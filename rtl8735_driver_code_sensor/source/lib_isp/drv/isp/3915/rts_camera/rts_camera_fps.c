/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_fps.c
 *
 * Copyright (C) 2017      Wil shi<wil_shi@realsil.com.cn>
 */


#include "cmsis_os2.h"
#include <errno.h>
#include "rts_errno.h"
#include <rtscamkit.h>
#include "rts_camera_fps.h"
#include "rts_camera.h"
#include "rts_camera_priv.h"
#include "isp_debug.h"

static void __rtscam_get_sensor_maxfps(struct rtscam_video_fps *fps, int *n);
static int __rtscam_check_sensor_fps(struct rtscam_video_fps *fps, int n);
static void __rtscam_update_sensor_fps_dynamic(
			struct rtscam_video_stream *stream, u32 fps);


static int __calc_coprime(int *a, int *b)
{
	int m = *a;
	int n = *b;

	if (m < 0 || n < 0)
		return 0;
	if (m == 0)
		return n;
	if (n == 0)
		return m;

	while (n != 0) {
		int tmp = m % n;

		m = n;
		n = tmp;
	}
	*a = (*a) / m;
	*b = (*b) / m;

	return m;
}

static void __rtscam_init_skip_info(struct rtscam_video_stream *stream)
{
	struct rtscam_soc_skip_info *skip = NULL;

	if (stream->streamid >= stream->fps.sensor_fps->streamnum)
		return;

	skip = &stream->fps.skip_info;

	skip->m = stream->fps.sensor_fps->sensor_fps_actual;
	skip->n = stream->fps.user_actual.denominator
			/ stream->fps.user_actual.numerator;

	__calc_coprime(&skip->m, &skip->n);

	if (skip->m > 2 * skip->n) {
		skip->flag = 1;
	} else {
		skip->flag = 0;
		skip->n = skip->m - skip->n;
	}
	skip->count = 0;
	skip->index = 0;
#ifdef _FPS_LOG_
	printf("s%d fps_act %d user %d/%d skip flag %d m %d n %d \n", stream->streamid , stream->fps.sensor_fps->sensor_fps_actual, stream->fps.user_actual.denominator,
			stream->fps.user_actual.numerator, skip->flag, skip->m, skip->n);
#endif
}

int rtscam_skip_frame(struct rtscam_video_stream *stream)
{
	struct rtscam_soc_skip_info *skip_info = NULL;
	int skip = 0;

	if (stream->streamid >= stream->fps.sensor_fps->streamnum)
		return 0;

	skip_info = &stream->fps.skip_info;

	rtsprintk(RTS_TRACE_VIDEO, "%d %d %d %d %d\n",
		  skip_info->m, skip_info->n, skip_info->flag,
		  skip_info->count, skip_info->index);

	if (skip_info->n == 0)
		return skip_info->flag;

	if ((skip_info->n - skip_info->count) * skip_info->m >=
	    (skip_info->m - skip_info->index) * skip_info->n) {
		skip = 1 - skip_info->flag;
		skip_info->count++;
	} else {
		skip = skip_info->flag;
	}

	skip_info->index++;
	if (skip_info->index % skip_info->m == 0) {
		skip_info->count = 0;
		skip_info->index = 0;
	}

	return skip;
}
//EXPORT_SYMBOL_GPL(rtscam_skip_frame);

static void __update_user_fps_actual(struct rtscam_video_fps *fps,
				     u32 user_numerator,
				     u32 user_denominator)
{
	if (!fps)
		return;

	fps->user_actual.numerator = user_numerator;
	fps->user_actual.denominator = user_denominator;
}

void rtscam_adjust_sensor_fps_dynamic(struct rtscam_video_stream *stream,
		u32 user_numerator, u32 user_denominator)
{
	struct rtscam_video_fps *fps = &stream->fps;
	int fps_max;
	int fps_current;
	int fps_before;
	u32 fps_set;

	if (!vb2_is_streaming(&stream->vb2_vidp))  // almost return because we only run rtscam_set_user_frmival at open stream
		return;

	if (fps->sensor_fps->flag_max)
		return;

	fps_current = user_denominator / user_numerator;
	fps_before = stream->fps.user_setting.denominator /
		stream->fps.user_setting.numerator;
	__rtscam_get_sensor_maxfps(fps, &fps_max);
#ifdef _FPS_LOG_
	printf("cur %d bef %d max %d \n", fps_current, fps_before, fps_max);
#endif
	if (fps_current == fps_before)
		return;

	if (fps_current > fps_before && fps_current <= fps_max)
		return;

	if (fps_current < fps_before && fps_before <= fps_max)
		return;

	fps_set = fps_current > fps_max ? fps_current : fps_max;

	fps_set = __rtscam_check_sensor_fps(fps, fps_set);
	if (fps_set != 0)
		__rtscam_update_sensor_fps_dynamic(stream, fps_set);
}
//EXPORT_SYMBOL_GPL(rtscam_adjust_sensor_fps_dynamic);

void rtscam_set_user_fps(struct rtscam_video_fps *fps,
				u32 user_numerator, u32 user_denominator)
{
	struct rtscam_video_stream *stream;

	if (!fps)
		return;

	stream = container_of(fps, struct rtscam_video_stream, fps);

	rtscam_adjust_sensor_fps_dynamic(stream,
			user_numerator, user_denominator);

	fps->user_setting.numerator = user_numerator;
	fps->user_setting.denominator = user_denominator;
#ifdef _FPS_LOG_
	printf("%s user %d/%d act %d set %d \n", __func__, user_numerator, user_denominator, fps->sensor_fps->sensor_fps_actual, fps->sensor_fps->sensor_fps_setting);
#endif
	if (user_denominator / user_numerator <=
			fps->sensor_fps->sensor_fps_actual)
		__update_user_fps_actual(fps,
				fps->user_setting.numerator,
				fps->user_setting.denominator);
	else
		__update_user_fps_actual(fps,
			1, fps->sensor_fps->sensor_fps_actual);

	__rtscam_init_skip_info(stream);
}
//EXPORT_SYMBOL_GPL(rtscam_set_user_fps);

static void __set_sensor_fps(struct rtscam_sensor_fps *sensor_fps, u32 fps)
{
	if (!sensor_fps)
		return;

	if (sensor_fps->sensor_fps_setting == fps)
		return;

	sensor_fps->sensor_fps_setting = fps;
}

static void __update_sensor_fps_actual(
			struct rtscam_sensor_fps *sensor_fps, u8 val)
{
	int i;
	int fps_user_setting;
	int fps_user_actual;
	struct rtscam_video_stream *stream;
	struct v4l2_fract *fract;

	if (!sensor_fps)
		return;

	if (sensor_fps->sensor_fps_actual == val)
		return;

	
	//if (sensor_fps->sensor_fps_actual < val)    // [To Be comfirm with PC] let change sensor fps from high to low
		sensor_fps->sensor_fps_actual = val;

	for (i = 0; i < sensor_fps->streamnum; i++) {
		stream = sensor_fps->streams + i;
		if (!vb2_is_streaming(&stream->vb2_vidp))   // [To Be comfirm with PC]  skip no-running stream
			continue;
		fract = &stream->fps.user_setting;
		fps_user_setting = fract->denominator / fract->numerator;
		fract = &stream->fps.user_actual;
		fps_user_actual = fract->denominator / fract->numerator;
#ifdef _FPS_LOG_
		printf("s%d set %d act %d snr act %d set %d \n", i, fps_user_setting, fps_user_actual, (int)sensor_fps->sensor_fps_actual, (int)sensor_fps->sensor_fps_setting);
#endif
		if (fps_user_setting > (int)sensor_fps->sensor_fps_actual) {
			__update_user_fps_actual(&stream->fps,
						 1,
						 sensor_fps->sensor_fps_actual);
		} else if (fps_user_setting != fps_user_actual) {
			fract = &stream->fps.user_setting;
			__update_user_fps_actual(&stream->fps,
						 fract->numerator,
						 fract->denominator);
		}

		__rtscam_init_skip_info(stream);
	}
}

static void __rtscam_get_sensor_maxfps(struct rtscam_video_fps *fps, int *n)
{
	int i;
	int n_tmp;
	int n_max = 0;
	struct rtscam_video_stream *stream;
	struct rtscam_video_stream *stream_tmp;

	stream = container_of(fps, struct rtscam_video_stream, fps);
	for (i = 0; i < fps->sensor_fps->streamnum; i++) {
		stream_tmp = fps->sensor_fps->streams + i;
		if (stream_tmp->streamid == stream->streamid)
			continue;
		if (vb2_is_streaming(&stream_tmp->vb2_vidp)) {
			n_tmp = stream_tmp->fps.user_setting.denominator
				/ stream_tmp->fps.user_setting.numerator;
			if (n_tmp > n_max)
				n_max = n_tmp;
		}
	}
	*n = n_max;
}

static int __rtscam_check_sensor_fps(struct rtscam_video_fps *fps, int n)
{
	int i;
	int m;
	int m_tmp;
	int flag  = 0;
	u32 ret;
	struct rtscam_sensor_fps *sensor_fps;

	sensor_fps = fps->sensor_fps;
	m = sensor_fps->sensor_fps_setting;
	if (*fps->sensor_fps->streaming_count == 0)
		m = 0;

	for (i = 0; i < sensor_fps->desc.length; i++) {
		if (!sensor_fps->desc.fps[i])
			break;

		m_tmp = sensor_fps->desc.fps[i];
		if ((m < n && m_tmp >= n) || (m > m_tmp && m_tmp >= n)) {
			m = m_tmp;
			ret = m_tmp;
			flag = 1;
		}
	}
	if (flag)
		return ret;
	else
		return 0;
}

static int __rtscam_update_sensor_fps(struct rtscam_video_fps *fps,
					u32 val, int flag)
{
	int i;
	int ret;
	struct rtscam_video_stream *stream_tmp;
	struct rtscam_video_stream *stream = container_of(
				fps, struct rtscam_video_stream, fps);
	struct rtscam_sensor_fps *sensor_fps = fps->sensor_fps;

	if (val > RTSCAM_SOC_MAX_FPS) {
		isp_error("%s:fps %d is too large\n", __func__, val);
		return -EINVAL;
	}

	for (i = 0; i < sensor_fps->streamnum; i++) {
		stream_tmp = sensor_fps->streams + i;

		if (stream_tmp->streamid == stream->streamid && flag)
			continue;

		if (!vb2_is_streaming(&stream_tmp->vb2_vidp))
			continue;

		sensor_fps->set_stream(stream_tmp, 0);
	}
#ifdef _FPS_LOG_
	printf("%s actual %d fps %d \r\n",__FUNCTION__, sensor_fps->sensor_fps_actual, val);
#endif
	if (sensor_fps->sensor_fps_actual < val)
	{
		ret = sensor_fps->set_fps(stream, val);
		if (ret == 0) {
			__set_sensor_fps(sensor_fps, val);
			__update_sensor_fps_actual(sensor_fps, val);
		} else {
			isp_error("%s:set fps fail ret = %d \n", __func__, ret);
		}
	}

	for (i = 0; i < sensor_fps->streamnum; i++) {
		stream_tmp = sensor_fps->streams + i;

		if (stream_tmp->streamid == stream->streamid && flag)
			continue;

		if (!vb2_is_streaming(&stream_tmp->vb2_vidp))
			continue;

		sensor_fps->set_stream(stream_tmp, 1);
	}

	return ret;
}

int rtscam_update_sensor_fps(struct rtscam_video_stream *stream,
				u32 fps)
{
	struct rtscam_video_fps *stream_fps = &stream->fps;

	return __rtscam_update_sensor_fps(stream_fps, fps, 0);
}
//EXPORT_SYMBOL_GPL(rtscam_update_sensor_fps);

static void __rtscam_update_sensor_fps_dynamic(
			struct rtscam_video_stream *stream, u32 fps)
{
	struct rtscam_video_fps *stream_fps = &stream->fps;
	struct rtscam_sensor_fps *sensor_fps = stream_fps->sensor_fps;
	int ret;

	if (fps > RTSCAM_SOC_MAX_FPS) {
		isp_error( "%s : fps %d is too large\n", __func__, fps);
		return;
	}

	ret = sensor_fps->set_fps_dynamic(stream, fps);
	if (ret == 0) {
		__set_sensor_fps(sensor_fps, fps);
		printf("dynamic set fps %d -> %d ok\n", sensor_fps->sensor_fps_actual, fps);
		__update_sensor_fps_actual(sensor_fps, fps);

	} else {
		isp_error(" %s set_fps_dynamic fail %d\n", __func__, ret);
	}
}

void rtscam_adjust_sensor_fps(struct rtscam_video_stream *stream, int enable)
{
	int fps_max;
	int fps_cur;
	int fps_set;
	struct rtscam_video_fps *fps = &stream->fps;
	struct rtscam_sensor_fps *sensor_fps;

	sensor_fps = fps->sensor_fps;
	if (stream->streamid >= sensor_fps->streamnum)
		return;

	fps_cur = fps->user_setting.denominator
			/ fps->user_setting.numerator;
	__rtscam_get_sensor_maxfps(fps, &fps_max);
#ifdef _FPS_LOG_
	printf("cur %d max %d setting %d act %d \n", fps_cur, fps_max, sensor_fps->sensor_fps_setting, sensor_fps->sensor_fps_actual);
#endif
	if (fps_cur > fps_max) {
		if (enable)
			fps_set = fps_cur;
		else
			fps_set = fps_max;
	} else {
		if (sensor_fps->sensor_fps_setting != sensor_fps->sensor_fps_actual) {
			printf("sensor_fps_setting mismatch set %d act %d \n", sensor_fps->sensor_fps_setting, sensor_fps->sensor_fps_actual);
			//__rtscam_update_sensor_fps(fps, sensor_fps->sensor_fps_setting, 1);
			__rtscam_update_sensor_fps_dynamic(stream, sensor_fps->sensor_fps_setting);  
			// [To Be comfirm with PC]  change to update sensor fps without restart other stream
			// but can't find the case enter this condition
		}
		goto exit;
	}

	if (!enable && vb2_is_streaming(&stream->vb2_vidp) &&
	    *fps->sensor_fps->streaming_count == 1)
		goto exit;

	fps_set = __rtscam_check_sensor_fps(fps, fps_set);
#ifdef _FPS_LOG_
	printf("fps_set %d \n", fps_set);
#endif
	if (fps_set != 0)
		//__rtscam_update_sensor_fps(fps, fps_set, 1);
		__rtscam_update_sensor_fps_dynamic(stream, fps_set);
		// [To Be comfirm with PC]  change to update sensor fps without restart other stream
exit:
	if (enable)
		__rtscam_init_skip_info(stream);
}
//EXPORT_SYMBOL_GPL(rtscam_adjust_sensor_fps);

void rtscam_exec_sensor_fps_setting(
		struct rtscam_video_stream *stream, int enable)
{
	struct rtscam_sensor_fps *sensor_fps = stream->fps.sensor_fps;
#ifdef _FPS_LOG_
	printf("%s fps %d \r\n",__FUNCTION__, sensor_fps->sensor_fps_setting);
#endif
	if (!stream->icd->streaming_count) {
		sensor_fps->set_fps(stream,
				sensor_fps->sensor_fps_setting);
		__update_sensor_fps_actual(sensor_fps,
				sensor_fps->sensor_fps_setting);
	}

	if (enable)
		__rtscam_init_skip_info(stream);

}
//EXPORT_SYMBOL_GPL(rtscam_exec_sensor_fps_setting);

void rtscam_enable_snr_fps_max(struct rtscam_sensor_fps *sensor_fps)
{
	u32 fps;
	int i;

	if (!sensor_fps)
		return;

	if (sensor_fps->flag_max)
		return;

	if (*sensor_fps->streaming_count) {
		rtsprintk(RTS_TRACE_INFO, "please stop streaming first\n");
		return;
	}

	fps = sensor_fps->desc.fps[0];
	for (i = 0; i < sensor_fps->desc.length; i++) {
		if (!sensor_fps->desc.fps[i])
			break;
		if (fps < sensor_fps->desc.fps[i])
			fps = sensor_fps->desc.fps[i];
	}
	if (!fps) {
		rtsprintk(RTS_TRACE_ERROR, "there is no max fps\n");
		return;
	}

	__set_sensor_fps(sensor_fps, fps);
	sensor_fps->flag_max = 1;
}
//EXPORT_SYMBOL_GPL(rtscam_enable_snr_fps_max);

void rtscam_disable_snr_fps_max(struct rtscam_sensor_fps *sensor_fps)
{
	if (!sensor_fps)
		return;

	if (!sensor_fps->flag_max)
		return;

	if (*sensor_fps->streaming_count) {
		rtsprintk(RTS_TRACE_INFO, "please stop streaming first\n");
		return;
	}

	sensor_fps->flag_max = 0;
}
//EXPORT_SYMBOL_GPL(rtscam_disable_snr_fps_max);

int rtscam_change_dynamic_fps(struct rtscam_sensor_fps *sensor_fps, u16 fps)
{
	if (!sensor_fps)
		return -EINVAL;

	if (fps <= 0 || fps > sensor_fps->sensor_fps_setting) {
		isp_error("invalid dynamic fps : %d\n", fps);
		return -EINVAL;
	}
	__update_sensor_fps_actual(sensor_fps, fps);
#ifdef _FPS_LOG_
	printf("dynamic fps change to: %d set %d \n", sensor_fps->sensor_fps_actual, fps);
#endif

	return 0;
}
//EXPORT_SYMBOL_GPL(rtscam_change_dynamic_fps);

struct rtscam_video_frmival *rtscam_get_video_frmival(
		struct rtscam_video_stream *stream, u32 fourcc,
		u32 width, u32 height)
{
	struct rtscam_video_format *format;
	struct rtscam_video_frmival *frmival = NULL;

	format = find_format_by_fourcc(stream, fourcc);

	if (format == NULL) {
		printf("please register format(%c%c%c%c) first\n", v4l2pixfmtstr(fourcc));
		return NULL;
	}

	if (format->frame_type == RTSCAM_SIZE_STEPWISE ||
	    format->frame_type == RTSCAM_SIZE_CONTINUOUS) {
		if (width < format->stepwise.min.width)
			return NULL;
		if (width > format->stepwise.max.width)
			return NULL;
		if ((width - format->stepwise.min.width) %
		    format->stepwise.step.width != 0)
			return NULL;
		if (height < format->stepwise.min.height)
			return NULL;
		if (height > format->stepwise.max.height)
			return NULL;
		if ((height - format->stepwise.min.height) %
		    format->stepwise.step.height != 0)
			return NULL;
		frmival = &format->stepwise.frmival;
	} else if (format->frame_type == RTSCAM_SIZE_DISCRETE) {
		struct rtscam_video_frame *frame = find_frame(format,
							      width, height);
		if (frame == NULL){
			printf("find_frame error\n");
			return NULL;
		}
		frmival = &frame->frmival;
	}

	return frmival;
}

int rtscam_register_frmival_discrete(struct rtscam_video_stream *stream,
				     __u32 fourcc,
				     struct rtscam_frame_size *size)
{
	struct rtscam_video_frmival *frmival = NULL;
	u32 fps = stream->fps.sensor_fps->sensor_fps_setting;

	if (fps > RTSCAM_SOC_MAX_FPS)
		fps = RTSCAM_SOC_MAX_FPS;
	frmival = rtscam_get_video_frmival(stream, fourcc,
			size->width, size->height);
	if (frmival == NULL) {
		printf("rtscam_get_video_frmival error\n");
		return -EINVAL;
	}


	if (frmival->initialized &&
	    frmival->frmival_type != RTSCAM_SIZE_DISCRETE){
		printf("frmival_type error %d\n", frmival->frmival_type);
		return -EINVAL;
	}

	if (stream->user_format == fourcc &&
	    stream->user_width == size->width &&
	    stream->user_height == size->height) {
#ifdef _FPS_LOG_
		printf("%s s%d w %ld h %ld fps %d \n", __func__, stream->streamid, stream->user_width, stream->user_height, fps);
#endif
		rtscam_set_user_fps(&stream->fps, 1, fps);
	}

	frmival->discrete.frmivals = stream->fps.sensor_fps->frmivals;
	frmival->initialized = 1;
	frmival->frmival_type = RTSCAM_SIZE_DISCRETE;
	return 0;
}
//EXPORT_SYMBOL_GPL(rtscam_register_frmival_discrete);

int rtscam_clr_frmival(struct rtscam_video_frmival *frmival)
{
	if (!frmival->initialized)
		return 0;

	if (frmival->frmival_type == RTSCAM_SIZE_DISCRETE)
		frmival->discrete.frmivals = NULL;

	frmival->initialized = 0;

	return 0;
}

static u32 __get_next_small_fps(u32 fth)
{
	u32 a;

	if (fth > RTSCAM_SOC_MAX_FPS)
		return RTSCAM_SOC_MAX_FPS;
	if (fth == 2)
		return 1;
	if (fth == 1)
		return 0;

	a = (RTSCAM_SOC_MAX_FPS - fth) / RTSCAM_SOC_STEP_FPS;
	a = RTSCAM_SOC_MAX_FPS - a * RTSCAM_SOC_STEP_FPS;

	if (a > RTSCAM_SOC_STEP_FPS)
		return a - RTSCAM_SOC_STEP_FPS;
	return 2;
}

static int __rtscam_register_frmival_discrete(
		struct rtscam_sensor_fps *sensor_fps, struct v4l2_fract *ival)
{
	struct rtscam_frame_frmival *p;
	struct rtscam_frame_frmival *fival;

	p = sensor_fps->frmivals;
	while (p) {
		if (p->frmival.numerator == ival->numerator &&
		    p->frmival.denominator == ival->denominator)
			return -EEXIST;
		p = p->next;
	}
	fival = rts_calloc(1, sizeof(*fival));
	if (!fival)
		return -ENOMEM;

	fival->frmival.numerator = ival->numerator;
	fival->frmival.denominator = ival->denominator;
	fival->next = NULL;

	if (sensor_fps->frmivals == NULL) {
		sensor_fps->frmivals = fival;
	} else {
		p = sensor_fps->frmivals;
		while (p->next)
			p = p->next;
		p->next = fival;
	}

	return 0;
}

int rtscam_release_sensor_fps(struct rtscam_sensor_fps *sensor_fps)
{
	struct rtscam_frame_frmival *p;
	struct rtscam_frame_frmival *next;

	if (!sensor_fps)
		return -EINVAL;

	p = sensor_fps->frmivals;
	while (p) {
		next = p->next;
		rts_free(p);
		p = next;
	}
	sensor_fps->frmivals = NULL;
	return 0;
}
//EXPORT_SYMBOL_GPL(rtscam_release_sensor_fps);

int rtscam_init_sensor_fps(struct rtscam_sensor_fps *sensor_fps, int flag_max)
{
	int i;
	int ret;
	u32 fps = 0;
	struct rtscam_soc_fps_descriptor *desc = &sensor_fps->desc;

	if (!sensor_fps)
		return -EINVAL;

	sensor_fps->flag_max = flag_max;
	for (i = 0; i < desc->length; i++) {
		u32 tmp = desc->fps[i];

		if (!tmp)
			break;
		if (fps < tmp)
			fps = tmp;
	}
	if (fps > RTSCAM_SOC_MAX_FPS)
		fps = RTSCAM_SOC_MAX_FPS;
#ifdef _FPS_LOG_
	printf("%s set fps %d \n", __func__, fps);
#endif
	__set_sensor_fps(sensor_fps, fps);

	while (fps > 0) {
		struct v4l2_fract ival;

		ival.numerator = 1;
		ival.denominator = fps;
		ret = __rtscam_register_frmival_discrete(
				      sensor_fps, &ival);
		if (ret)
			goto error;
		fps = __get_next_small_fps(fps);
	}
	return 0;

error:
	rtscam_release_sensor_fps(sensor_fps);
	return ret;
}
//EXPORT_SYMBOL_GPL(rtscam_init_sensor_fps);
