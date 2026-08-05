/*
 * Ported from linux driver
 */

/*
 * Copyright (C) 2010  Hans Verkuil <hverkuil@xs4all.nl>
 */

#include <rts_isp_errno.h>
#include <isp_atomic.h>
#include <isp_utils.h>
#include <isp_log.h>
#include <isp_mem.h>
#include <isp_v4l2_ctrl.h>
#include <dlist.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_V4L2

#undef has_op
#define has_op(master, op) \
	(master->ops && master->ops->op)
#define call_op(master, op) \
	(has_op(master, op) ? master->ops->op(master) : 0)

#define do_div(n, base) ({ \
	uint32_t __base = (base); \
	uint32_t __rem; \
	__rem = ((uint64_t)(n)) % __base; \
	(n) = ((uint64_t)(n)) / __base; \
	__rem; \
})

struct v4l2_ctrl_helper {
	/* Pointer to the control reference of the master control */
	struct v4l2_ctrl_ref *mref;
	/* The control corresponding to the v4l2_ext_control ID field. */
	struct v4l2_ctrl *ctrl;
	/* index of the next control belonging to the same cluster */
	uint32_t next;
};

static int is_cur_manual(const struct v4l2_ctrl *master)
{
	return master->is_auto && master->cur.val == master->manual_mode_value;
}

static int is_new_manual(const struct v4l2_ctrl *master)
{
	return master->is_auto && master->val == master->manual_mode_value;
}

static const char * const *rtsv_ctrl_get_menu(uint32_t id)
{
	static const char * const camera_power_line_frequency[] = {
		"Disabled",
		"50 Hz",
		"60 Hz",
		"Auto",
		NULL
	};
	static const char * const camera_exposure_auto[] = {
		"Auto Mode",
		"Manual Mode",
		"Shutter Priority Mode",
		"Aperture Priority Mode",
		NULL
	};
	static const char * const camera_exposure_metering[] = {
		"Average",
		"Center Weighted",
		"Spot",
		"Matrix",
		NULL
	};
	static const char * const camera_auto_focus_range[] = {
		"Auto",
		"Normal",
		"Macro",
		"Infinity",
		NULL
	};
	static const char * const colorfx[] = {
		"None",
		"Black & White",
		"Sepia",
		"Negative",
		"Emboss",
		"Sketch",
		"Sky Blue",
		"Grass Green",
		"Skin Whiten",
		"Vivid",
		"Aqua",
		"Art Freeze",
		"Silhouette",
		"Solarization",
		"Antique",
		"Set Cb/Cr",
		NULL
	};
	static const char * const auto_n_preset_white_balance[] = {
		"Manual",
		"Auto",
		"Incandescent",
		"Fluorescent",
		"Fluorescent H",
		"Horizon",
		"Daylight",
		"Flash",
		"Cloudy",
		"Shade",
		NULL,
	};
	static const char * const camera_iso_sensitivity_auto[] = {
		"Manual",
		"Auto",
		NULL
	};
	static const char * const scene_mode[] = {
		"None",
		"Backlight",
		"Beach/Snow",
		"Candle Light",
		"Dusk/Dawn",
		"Fall Colors",
		"Fireworks",
		"Landscape",
		"Night",
		"Party/Indoor",
		"Portrait",
		"Sports",
		"Sunset",
		"Text",
		NULL
	};

	static const char * const flash_led_mode[] = {
		"Off",
		"Flash",
		"Torch",
		NULL,
	};
	static const char * const flash_strobe_source[] = {
		"Software",
		"External",
		NULL,
	};

	switch (id) {
	case V4L2_CID_POWER_LINE_FREQUENCY:
		return camera_power_line_frequency;
	case V4L2_CID_EXPOSURE_AUTO:
		return camera_exposure_auto;
	case V4L2_CID_EXPOSURE_METERING:
		return camera_exposure_metering;
	case V4L2_CID_AUTO_FOCUS_RANGE:
		return camera_auto_focus_range;
	case V4L2_CID_COLORFX:
		return colorfx;
	case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		return auto_n_preset_white_balance;
	case V4L2_CID_ISO_SENSITIVITY_AUTO:
		return camera_iso_sensitivity_auto;
	case V4L2_CID_SCENE_MODE:
		return scene_mode;
	case V4L2_CID_FLASH_LED_MODE:
		return flash_led_mode;
	case V4L2_CID_FLASH_STROBE_SOURCE:
		return flash_strobe_source;

	default:
		return NULL;
	}
}

static const char *rtsv_ctrl_get_name(uint32_t id)
{
	switch (id) {
	/* USER controls */
	case V4L2_CID_USER_CLASS:
		return "User Controls";
	case V4L2_CID_BRIGHTNESS:
		return "Brightness";
	case V4L2_CID_CONTRAST:
		return "Contrast";
	case V4L2_CID_SATURATION:
		return "Saturation";
	case V4L2_CID_HUE:
		return "Hue";
	case V4L2_CID_AUDIO_VOLUME:
		return "Volume";
	case V4L2_CID_AUDIO_BALANCE:
		return "Balance";
	case V4L2_CID_AUDIO_BASS:
		return "Bass";
	case V4L2_CID_AUDIO_TREBLE:
		return "Treble";
	case V4L2_CID_AUDIO_MUTE:
		return "Mute";
	case V4L2_CID_AUDIO_LOUDNESS:
		return "Loudness";
	case V4L2_CID_BLACK_LEVEL:
		return "Black Level";
	case V4L2_CID_AUTO_WHITE_BALANCE:
		return "White Balance, Automatic";
	case V4L2_CID_DO_WHITE_BALANCE:
		return "Do White Balance";
	case V4L2_CID_RED_BALANCE:
		return "Red Balance";
	case V4L2_CID_BLUE_BALANCE:
		return "Blue Balance";
	case V4L2_CID_GAMMA:
		return "Gamma";
	case V4L2_CID_EXPOSURE:
		return "Exposure";
	case V4L2_CID_AUTOGAIN:
		return "Gain, Automatic";
	case V4L2_CID_GAIN:
		return "Gain";
	case V4L2_CID_HFLIP:
		return "Horizontal Flip";
	case V4L2_CID_VFLIP:
		return "Vertical Flip";
	case V4L2_CID_POWER_LINE_FREQUENCY:
		return "Power Line Frequency";
	case V4L2_CID_HUE_AUTO:
		return "Hue, Automatic";
	case V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		return "White Balance Temperature";
	case V4L2_CID_SHARPNESS:
		return "Sharpness";
	case V4L2_CID_BACKLIGHT_COMPENSATION:
		return "Backlight Compensation";
	case V4L2_CID_CHROMA_AGC:
		return "Chroma AGC";
	case V4L2_CID_COLOR_KILLER:
		return "Color Killer";
	case V4L2_CID_COLORFX:
		return "Color Effects";
	case V4L2_CID_AUTOBRIGHTNESS:
		return "Brightness, Automatic";
	case V4L2_CID_BAND_STOP_FILTER:
		return "Band-Stop Filter";
	case V4L2_CID_ROTATE:
		return "Rotate";
	case V4L2_CID_BG_COLOR:
		return "Background Color";
	case V4L2_CID_CHROMA_GAIN:
		return "Chroma Gain";
	case V4L2_CID_ILLUMINATORS_1:
		return "Illuminator 1";
	case V4L2_CID_ILLUMINATORS_2:
		return "Illuminator 2";
	case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		return "Min Number of Capture Buffers";
	case V4L2_CID_MIN_BUFFERS_FOR_OUTPUT:
		return "Min Number of Output Buffers";
	case V4L2_CID_ALPHA_COMPONENT:
		return "Alpha Component";
	case V4L2_CID_COLORFX_CBCR:
		return "Color Effects, CbCr";

	/* CAMERA controls */
	case V4L2_CID_CAMERA_CLASS:
		return "Camera Controls";
	case V4L2_CID_EXPOSURE_AUTO:
		return "Auto Exposure";
	case V4L2_CID_EXPOSURE_ABSOLUTE:
		return "Exposure Time, Absolute";
	case V4L2_CID_EXPOSURE_AUTO_PRIORITY:
		return "Exposure, Dynamic Framerate";
	case V4L2_CID_PAN_RELATIVE:
		return "Pan, Relative";
	case V4L2_CID_TILT_RELATIVE:
		return "Tilt, Relative";
	case V4L2_CID_PAN_RESET:
		return "Pan, Reset";
	case V4L2_CID_TILT_RESET:
		return "Tilt, Reset";
	case V4L2_CID_PAN_ABSOLUTE:
		return "Pan, Absolute";
	case V4L2_CID_TILT_ABSOLUTE:
		return "Tilt, Absolute";
	case V4L2_CID_FOCUS_ABSOLUTE:
		return "Focus, Absolute";
	case V4L2_CID_FOCUS_RELATIVE:
		return "Focus, Relative";
	case V4L2_CID_FOCUS_AUTO:
		return "Focus, Automatic Continuous";
	case V4L2_CID_ZOOM_ABSOLUTE:
		return "Zoom, Absolute";
	case V4L2_CID_ZOOM_RELATIVE:
		return "Zoom, Relative";
	case V4L2_CID_ZOOM_CONTINUOUS:
		return "Zoom, Continuous";
	case V4L2_CID_PRIVACY:
		return "Privacy";
	case V4L2_CID_IRIS_ABSOLUTE:
		return "Iris, Absolute";
	case V4L2_CID_IRIS_RELATIVE:
		return "Iris, Relative";
	case V4L2_CID_AUTO_EXPOSURE_BIAS:
		return "Auto Exposure, Bias";
	case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		return "White Balance, Auto & Preset";
	case V4L2_CID_WIDE_DYNAMIC_RANGE:
		return "Wide Dynamic Range";
	case V4L2_CID_IMAGE_STABILIZATION:
		return "Image Stabilization";
	case V4L2_CID_ISO_SENSITIVITY:
		return "ISO Sensitivity";
	case V4L2_CID_ISO_SENSITIVITY_AUTO:
		return "ISO Sensitivity, Auto";
	case V4L2_CID_EXPOSURE_METERING:
		return "Exposure, Metering Mode";
	case V4L2_CID_SCENE_MODE:
		return "Scene Mode";
	case V4L2_CID_3A_LOCK:
		return "3A Lock";
	case V4L2_CID_AUTO_FOCUS_START:
		return "Auto Focus, Start";
	case V4L2_CID_AUTO_FOCUS_STOP:
		return "Auto Focus, Stop";
	case V4L2_CID_AUTO_FOCUS_STATUS:
		return "Auto Focus, Status";
	case V4L2_CID_AUTO_FOCUS_RANGE:
		return "Auto Focus, Range";
	case V4L2_CID_PAN_SPEED:
		return "Pan, Speed";
	case V4L2_CID_TILT_SPEED:
		return "Tilt, Speed";

	/* Flash controls */
	case V4L2_CID_FLASH_CLASS:
		return "Flash Controls";
	case V4L2_CID_FLASH_LED_MODE:
		return "LED Mode";
	case V4L2_CID_FLASH_STROBE_SOURCE:
		return "Strobe Source";
	case V4L2_CID_FLASH_STROBE:
		return "Strobe";
	case V4L2_CID_FLASH_STROBE_STOP:
		return "Stop Strobe";
	case V4L2_CID_FLASH_STROBE_STATUS:
		return "Strobe Status";
	case V4L2_CID_FLASH_TIMEOUT:
		return "Strobe Timeout";
	case V4L2_CID_FLASH_INTENSITY:
		return "Intensity, Flash Mode";
	case V4L2_CID_FLASH_TORCH_INTENSITY:
		return "Intensity, Torch Mode";
	case V4L2_CID_FLASH_INDICATOR_INTENSITY:
		return "Intensity, Indicator";
	case V4L2_CID_FLASH_FAULT:
		return "Faults";
	case V4L2_CID_FLASH_CHARGE:
		return "Charge";
	case V4L2_CID_FLASH_READY:
		return "Ready to Strobe";

	default:
		return NULL;
	}
}

static void rtsv_ctrl_fill(uint32_t id, const char **name,
			   enum v4l2_ctrl_type *type, int64_t *min,
			   int64_t *max, uint64_t *step, int64_t *def,
			   uint32_t *flags)
{
	*name = rtsv_ctrl_get_name(id);
	*flags = 0;

	switch (id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
	case V4L2_CID_AUTOGAIN:
	case V4L2_CID_HFLIP:
	case V4L2_CID_VFLIP:
	case V4L2_CID_HUE_AUTO:
	case V4L2_CID_CHROMA_AGC:
	case V4L2_CID_COLOR_KILLER:
	case V4L2_CID_AUTOBRIGHTNESS:
	case V4L2_CID_EXPOSURE_AUTO_PRIORITY:
	case V4L2_CID_FOCUS_AUTO:
	case V4L2_CID_PRIVACY:
	case V4L2_CID_ILLUMINATORS_1:
	case V4L2_CID_ILLUMINATORS_2:
	case V4L2_CID_FLASH_STROBE_STATUS:
	case V4L2_CID_FLASH_CHARGE:
	case V4L2_CID_FLASH_READY:
		*type = V4L2_CTRL_TYPE_BOOLEAN;
		*min = 0;
		*max = *step = 1;
		break;
	case V4L2_CID_PAN_RESET:
	case V4L2_CID_TILT_RESET:
	case V4L2_CID_FLASH_STROBE:
	case V4L2_CID_FLASH_STROBE_STOP:
	case V4L2_CID_AUTO_FOCUS_START:
	case V4L2_CID_AUTO_FOCUS_STOP:
		*type = V4L2_CTRL_TYPE_BUTTON;
		*flags |= V4L2_CTRL_FLAG_WRITE_ONLY |
			V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
		*min = *max = *step = *def = 0;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY:
	case V4L2_CID_EXPOSURE_AUTO:
	case V4L2_CID_AUTO_FOCUS_RANGE:
	case V4L2_CID_COLORFX:
	case V4L2_CID_FLASH_LED_MODE:
	case V4L2_CID_FLASH_STROBE_SOURCE:
	case V4L2_CID_ISO_SENSITIVITY_AUTO:
	case V4L2_CID_EXPOSURE_METERING:
	case V4L2_CID_SCENE_MODE:
	case V4L2_CID_TEST_PATTERN:
		*type = V4L2_CTRL_TYPE_MENU;
		break;
	case V4L2_CID_ISO_SENSITIVITY:
	case V4L2_CID_AUTO_EXPOSURE_BIAS:
		*type = V4L2_CTRL_TYPE_INTEGER_MENU;
		break;
	case V4L2_CID_USER_CLASS:
	case V4L2_CID_CAMERA_CLASS:
	case V4L2_CID_FLASH_CLASS:
		*type = V4L2_CTRL_TYPE_CTRL_CLASS;
		*flags |= V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_WRITE_ONLY;
		*min = *max = *step = *def = 0;
		break;
	case V4L2_CID_BG_COLOR:
		*type = V4L2_CTRL_TYPE_INTEGER;
		*step = 1;
		*min = 0;
		*max = 0xFFFFFF;
		break;
	case V4L2_CID_FLASH_FAULT:
	case V4L2_CID_3A_LOCK:
	case V4L2_CID_AUTO_FOCUS_STATUS:
		*type = V4L2_CTRL_TYPE_BITMASK;
		break;
	case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
	case V4L2_CID_MIN_BUFFERS_FOR_OUTPUT:
		*type = V4L2_CTRL_TYPE_INTEGER;
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		break;
	default:
		*type = V4L2_CTRL_TYPE_INTEGER;
		break;
	}
	switch (id) {
	case V4L2_CID_BRIGHTNESS:
	case V4L2_CID_CONTRAST:
	case V4L2_CID_SATURATION:
	case V4L2_CID_HUE:
	case V4L2_CID_RED_BALANCE:
	case V4L2_CID_BLUE_BALANCE:
	case V4L2_CID_GAMMA:
	case V4L2_CID_SHARPNESS:
	case V4L2_CID_CHROMA_GAIN:
		*flags |= V4L2_CTRL_FLAG_SLIDER;
		break;
	case V4L2_CID_PAN_RELATIVE:
	case V4L2_CID_TILT_RELATIVE:
	case V4L2_CID_FOCUS_RELATIVE:
	case V4L2_CID_IRIS_RELATIVE:
	case V4L2_CID_ZOOM_RELATIVE:
		*flags |= V4L2_CTRL_FLAG_WRITE_ONLY |
			V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
		break;
	case V4L2_CID_FLASH_STROBE_STATUS:
	case V4L2_CID_AUTO_FOCUS_STATUS:
	case V4L2_CID_FLASH_READY:
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		break;
	}
}

static uint32_t user_flags(const struct v4l2_ctrl *ctrl)
{
	uint32_t flags = ctrl->flags;

	if (ctrl->is_ptr)
		flags |= V4L2_CTRL_FLAG_HAS_PAYLOAD;

	return flags;
}

static int std_equal(const struct v4l2_ctrl *ctrl, uint32_t idx,
		     union v4l2_ctrl_ptr ptr1, union v4l2_ctrl_ptr ptr2)
{
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_BUTTON:
		return RTS_ISP_FALSE;
	case V4L2_CTRL_TYPE_STRING:
		idx *= ctrl->elem_size;
		/* strings are always 0-terminated */
		return !strcmp(ptr1.p_char + idx, ptr2.p_char + idx);
	case V4L2_CTRL_TYPE_INTEGER64:
		return ptr1.p_s64[idx] == ptr2.p_s64[idx];
	case V4L2_CTRL_TYPE_U8:
		return ptr1.p_u8[idx] == ptr2.p_u8[idx];
	case V4L2_CTRL_TYPE_U16:
		return ptr1.p_u16[idx] == ptr2.p_u16[idx];
	case V4L2_CTRL_TYPE_U32:
		return ptr1.p_u32[idx] == ptr2.p_u32[idx];
	default:
		if (ctrl->is_int)
			return ptr1.p_s32[idx] == ptr2.p_s32[idx];
		idx *= ctrl->elem_size;
		return !memcmp((void *)((u32)(ptr1.p) + idx), (void *)((u32)(ptr2.p) + idx), ctrl->elem_size);
	}
}

static void std_init(const struct v4l2_ctrl *ctrl, uint32_t idx,
		     union v4l2_ctrl_ptr ptr)
{
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_STRING:
		idx *= ctrl->elem_size;
		memset(ptr.p_char + idx, ' ', ctrl->minimum);
		ptr.p_char[idx + ctrl->minimum] = '\0';
		break;
	case V4L2_CTRL_TYPE_INTEGER64:
		ptr.p_s64[idx] = ctrl->default_value;
		break;
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_BITMASK:
	case V4L2_CTRL_TYPE_BOOLEAN:
		ptr.p_s32[idx] = ctrl->default_value;
		break;
	case V4L2_CTRL_TYPE_U8:
		ptr.p_u8[idx] = ctrl->default_value;
		break;
	case V4L2_CTRL_TYPE_U16:
		ptr.p_u16[idx] = ctrl->default_value;
		break;
	case V4L2_CTRL_TYPE_U32:
		ptr.p_u32[idx] = ctrl->default_value;
		break;
	default:
		idx *= ctrl->elem_size;
		memset((void *)((u32)(ptr.p) + idx), 0, ctrl->elem_size);
		break;
	}
}

static void std_log(const struct v4l2_ctrl *ctrl)
{
#if 0
	union v4l2_ctrl_ptr ptr = ctrl->p_cur;

	if (ctrl->is_array) {
		unsigned int i;

		for (i = 0; i < ctrl->nr_of_dims; i++)
			isp_info_cont("[%u]", ctrl->dims[i]);
		isp_info_cont(" ");
	}

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER:
		isp_info_cont("%d", *ptr.p_s32);
		break;
	case V4L2_CTRL_TYPE_BOOLEAN:
		isp_info_cont("%s", *ptr.p_s32 ? "true" : "false");
		break;
	case V4L2_CTRL_TYPE_MENU:
		isp_info_cont("%s", ctrl->qmenu[*ptr.p_s32]);
		break;
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		isp_info_cont("%lld", ctrl->qmenu_int[*ptr.p_s32]);
		break;
	case V4L2_CTRL_TYPE_BITMASK:
		isp_info_cont("0x%08x", *ptr.p_s32);
		break;
	case V4L2_CTRL_TYPE_INTEGER64:
		isp_info_cont("%lld", *ptr.p_s64);
		break;
	case V4L2_CTRL_TYPE_STRING:
		isp_info_cont("%s", ptr.p_char);
		break;
	case V4L2_CTRL_TYPE_U8:
		isp_info_cont("%u", (unsigned int)*ptr.p_u8);
		break;
	case V4L2_CTRL_TYPE_U16:
		isp_info_cont("%u", (unsigned int)*ptr.p_u16);
		break;
	case V4L2_CTRL_TYPE_U32:
		isp_info_cont("%u", (unsigned int)*ptr.p_u32);
		break;
	default:
		isp_info_cont("unknown type %d", ctrl->type);
		break;
	}
#endif
}

#define ROUND_TO_RANGE(val, offset_type, ctrl) ({ \
	offset_type offset; \
	if ((ctrl)->maximum >= 0 && \
	    val >= (ctrl)->maximum - (int32_t)((ctrl)->step / 2)) \
		val = (ctrl)->maximum; \
	else \
		val += (int32_t)((ctrl)->step / 2); \
	val = clamp_t(typeof(val), val, \
		      (ctrl)->minimum, (ctrl)->maximum); \
	offset = (val) - (ctrl)->minimum; \
	offset = (ctrl)->step * (offset / (uint32_t)(ctrl)->step); \
	val = (ctrl)->minimum + offset; \
	0; \
})

static int std_validate(const struct v4l2_ctrl *ctrl, uint32_t idx,
			union v4l2_ctrl_ptr ptr)
{
	int64_t len;
	uint64_t offset;
	int64_t val;

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER:
		return ROUND_TO_RANGE(ptr.p_s32[idx], uint32_t, ctrl);
	case V4L2_CTRL_TYPE_INTEGER64:
		val = ptr.p_s64[idx];
		if (ctrl->maximum >= 0 &&
		    val >= ctrl->maximum - (int64_t)(ctrl->step / 2))
			val = ctrl->maximum;
		else
			val += (int64_t)(ctrl->step / 2);
		val = clamp_t(int64_t, val, ctrl->minimum, ctrl->maximum);
		offset = val - ctrl->minimum;
		do_div(offset, ctrl->step);
		ptr.p_s64[idx] = ctrl->minimum + offset * ctrl->step;
		return 0;
	case V4L2_CTRL_TYPE_U8:
		return ROUND_TO_RANGE(ptr.p_u8[idx], uint8_t, ctrl);
	case V4L2_CTRL_TYPE_U16:
		return ROUND_TO_RANGE(ptr.p_u16[idx], uint16_t, ctrl);
	case V4L2_CTRL_TYPE_U32:
		return ROUND_TO_RANGE(ptr.p_u32[idx], uint32_t, ctrl);

	case V4L2_CTRL_TYPE_BOOLEAN:
		ptr.p_s32[idx] = !!ptr.p_s32[idx];
		return 0;

	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		if (ptr.p_s32[idx] < ctrl->minimum ||
		    ptr.p_s32[idx] > ctrl->maximum)
			return -RTS_ISP_ERANGE;
		if (ctrl->menu_skip_mask & ((uint64_t)1 << ptr.p_s32[idx]))
			return -RTS_ISP_EINVAL;
		if (ctrl->type == V4L2_CTRL_TYPE_MENU &&
		    ctrl->qmenu[ptr.p_s32[idx]][0] == '\0')
			return -RTS_ISP_EINVAL;
		return 0;

	case V4L2_CTRL_TYPE_BITMASK:
		ptr.p_s32[idx] &= ctrl->maximum;
		return 0;

	case V4L2_CTRL_TYPE_BUTTON:
	case V4L2_CTRL_TYPE_CTRL_CLASS:
		ptr.p_s32[idx] = 0;
		return 0;

	case V4L2_CTRL_TYPE_STRING:
		idx *= ctrl->elem_size;
		len = strlen(ptr.p_char + idx);
		if (len < ctrl->minimum)
			return -RTS_ISP_ERANGE;
		if ((len - (uint32_t)ctrl->minimum) % (uint32_t)ctrl->step)
			return -RTS_ISP_ERANGE;
		return 0;

	default:
		return -RTS_ISP_EINVAL;
	}
}

static const struct v4l2_ctrl_type_ops std_type_ops = {
	.equal = std_equal,
	.init = std_init,
	.log = std_log,
	.validate = std_validate,
};

static int ptr_to_user(struct v4l2_ext_control *c, struct v4l2_ctrl *ctrl,
		       union v4l2_ctrl_ptr ptr)
{
	uint32_t len;

	if (ctrl->is_ptr && !ctrl->is_string) {
		isp_memcpy(c->ptr, ptr.p, c->size);
		return 0;
	}

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_STRING:
		len = strlen(ptr.p_char);
		if (c->size < len + 1) {
			c->size = ctrl->elem_size;
			return -RTS_ISP_ENOSPC;
		}
		isp_memcpy(c->string, ptr.p_char, len + 1);
		return 0;
	case V4L2_CTRL_TYPE_INTEGER64:
		c->value64 = *ptr.p_s64;
		break;
	default:
		c->value = *ptr.p_s32;
		break;
	}
	return 0;
}

static int cur_to_user(struct v4l2_ext_control *c, struct v4l2_ctrl *ctrl)
{
	return ptr_to_user(c, ctrl, ctrl->p_cur);
}

static int new_to_user(struct v4l2_ext_control *c, struct v4l2_ctrl *ctrl)
{
	return ptr_to_user(c, ctrl, ctrl->p_new);
}

static int def_to_user(struct v4l2_ext_control *c, struct v4l2_ctrl *ctrl)
{
	uint32_t idx;

	for (idx = 0; idx < ctrl->elems; idx++)
		ctrl->type_ops->init(ctrl, idx, ctrl->p_new);

	return ptr_to_user(c, ctrl, ctrl->p_new);
}

static int user_to_ptr(struct v4l2_ext_control *c, struct v4l2_ctrl *ctrl,
		       union v4l2_ctrl_ptr ptr)
{
	uint32_t size;
	char last;

	ctrl->is_new = 1;
	if (ctrl->is_ptr && !ctrl->is_string) {
		unsigned int idx;

		isp_memcpy(ptr.p, c->ptr, c->size);
		if (!ctrl->is_array)
			return 0;
		for (idx = c->size / ctrl->elem_size; idx < ctrl->elems; idx++)
			ctrl->type_ops->init(ctrl, idx, ptr);
		return 0;
	}

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER64:
		*ptr.p_s64 = c->value64;
		break;
	case V4L2_CTRL_TYPE_STRING:
		size = c->size;
		if (size == 0)
			return -RTS_ISP_ERANGE;
		if (size > ctrl->maximum + 1)
			size = ctrl->maximum + 1;
		isp_memcpy(ptr.p_char, c->string, size);
		last = ptr.p_char[size - 1];
		ptr.p_char[size - 1] = 0;
		if ((int64_t)strlen(ptr.p_char) == ctrl->maximum && last)
			return -RTS_ISP_ERANGE;
		return 0;
	default:
		*ptr.p_s32 = c->value;
		break;
	}
	return 0;
}

static int user_to_new(struct v4l2_ext_control *c, struct v4l2_ctrl *ctrl)
{
	return user_to_ptr(c, ctrl, ctrl->p_new);
}

static void ptr_to_ptr(struct v4l2_ctrl *ctrl,
		       union v4l2_ctrl_ptr from, union v4l2_ctrl_ptr to)
{
	if (ctrl == NULL)
		return;
	isp_memcpy(to.p, from.p, ctrl->elems * ctrl->elem_size);
}

static void new_to_cur(struct v4l2_ctrl *ctrl, int update_flag)
{
	if (ctrl == NULL)
		return;
	if (!ctrl->has_changed && !update_flag)
		return;
	ptr_to_ptr(ctrl, ctrl->p_new, ctrl->p_cur);
}

static void cur_to_new(struct v4l2_ctrl *ctrl)
{
	if (ctrl == NULL)
		return;
	ptr_to_ptr(ctrl, ctrl->p_cur, ctrl->p_new);
}

static int cluster_changed(struct v4l2_ctrl *master)
{
	int changed = RTS_ISP_FALSE;
	unsigned int idx;
	int i;

	for (i = 0; i < (int)master->ncontrols; i++) {
		struct v4l2_ctrl *ctrl = master->cluster[i];
		int ctrl_changed = RTS_ISP_FALSE;

		if (ctrl == NULL)
			continue;

		if (ctrl->flags & V4L2_CTRL_FLAG_EXECUTE_ON_WRITE)
			changed = ctrl_changed = RTS_ISP_TRUE;

		if (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE) {
			ctrl->has_changed = RTS_ISP_FALSE;
			continue;
		}

		for (idx = 0; !ctrl_changed && idx < ctrl->elems; idx++)
			ctrl_changed = !ctrl->type_ops->equal(ctrl, idx,
							      ctrl->p_cur,
							      ctrl->p_new);
		ctrl->has_changed = ctrl_changed;
		changed |= ctrl->has_changed;
	}
	return changed;
}

static int check_range(enum v4l2_ctrl_type type,
		       int64_t min, int64_t max, uint64_t step, int64_t def)
{
	switch (type) {
	case V4L2_CTRL_TYPE_BOOLEAN:
		if (step != 1 || max > 1 || min < 0)
			return -RTS_ISP_ERANGE;
	/* fall through */
	case V4L2_CTRL_TYPE_U8:
	case V4L2_CTRL_TYPE_U16:
	case V4L2_CTRL_TYPE_U32:
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_INTEGER64:
		if (step == 0 || min > max || def < min || def > max)
			return -RTS_ISP_ERANGE;
		return 0;
	case V4L2_CTRL_TYPE_BITMASK:
		if (step || min || !max || (def & ~max))
			return -RTS_ISP_ERANGE;
		return 0;
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		if (min > max || def < min || def > max)
			return -RTS_ISP_ERANGE;
		/*
		 * Note: step == menu_skip_mask for menu controls.
		 * So here we check if the default value is masked out.
		 */
		if (step && (((uint64_t)1 << def) & step))
			return -RTS_ISP_EINVAL;
		return 0;
	case V4L2_CTRL_TYPE_STRING:
		if (min > max || min < 0 || step < 1 || def)
			return -RTS_ISP_ERANGE;
		return 0;
	default:
		return 0;
	}
}

static int validate_new(const struct v4l2_ctrl *ctrl, union v4l2_ctrl_ptr p_new)
{
	unsigned int idx;
	int err = 0;

	for (idx = 0; !err && idx < ctrl->elems; idx++)
		err = ctrl->type_ops->validate(ctrl, idx, p_new);
	return err;
}

static inline uint32_t node2id(struct isp_list *list)
{
	return list_data(list, struct v4l2_ctrl_ref, list)->ctrl->id;
}

static inline int handler_set_err(struct v4l2_ctrl_handler *hdl, int err)
{
	if (hdl->error == 0)
		hdl->error = err;
	return err;
}

int rtsv_ctrl_handler_init(struct v4l2_ctrl_handler *hdl, unsigned int nr_hint)
{
	list_init(&hdl->ctrls);
	list_init(&hdl->ctrl_refs);
	hdl->nr_of_buckets = 1 + nr_hint / 8;
	// coverity[bad_sizeof]
	isp_calloc_array(hdl->buckets, hdl->nr_of_buckets);
	hdl->error = hdl->buckets ? 0 : -RTS_ISP_ENOMEM;
	isp_info("%s ret %d \r\n", __FUNCTION__, hdl->error);
	return hdl->error;
}

void rtsv_ctrl_handler_free(struct v4l2_ctrl_handler *hdl)
{
	struct v4l2_ctrl_ref *ref, *next_ref;
	struct v4l2_ctrl *ctrl, *next_ctrl;

	if (hdl == NULL || hdl->buckets == NULL)
		return;

	list_foreach_data_safe(ref, next_ref, &hdl->ctrl_refs, list) {
		list_remove(&ref->list);
		isp_free(ref);
	}
	list_foreach_data_safe(ctrl, next_ctrl, &hdl->ctrls, list) {
		list_remove(&ctrl->list);
		isp_free(ctrl);
	}
	isp_free(hdl->buckets);
	hdl->buckets = NULL;
	hdl->cached = NULL;
	hdl->error = 0;
}

static struct v4l2_ctrl_ref *find_ref(struct v4l2_ctrl_handler *hdl,
				      uint32_t id)
{
	struct v4l2_ctrl_ref *ref;
	int bucket;

	id &= V4L2_CTRL_ID_MASK;

	if (id >= V4L2_CID_PRIVATE_BASE)
		return NULL;

	if (hdl->cached && hdl->cached->ctrl->id == id)
		return hdl->cached;

	bucket = id % hdl->nr_of_buckets;

	ref = hdl->buckets ? hdl->buckets[bucket] : NULL;
	while (ref && ref->ctrl->id != id)
		ref = ref->next;

	if (ref)
		hdl->cached = ref;
	return ref;
}

struct v4l2_ctrl *rtsv_ctrl_find(struct v4l2_ctrl_handler *hdl, uint32_t id)
{
	struct v4l2_ctrl_ref *ref = find_ref(hdl, id);

	return ref ? ref->ctrl : NULL;
}

static int handler_new_ref(struct v4l2_ctrl_handler *hdl,
			   struct v4l2_ctrl *ctrl)
{
	struct v4l2_ctrl_ref *ref;
	struct v4l2_ctrl_ref *new_ref;
	uint32_t id = ctrl->id;
	uint32_t class_ctrl = V4L2_CTRL_ID2WHICH(id) | 1;
	int bucket = id % hdl->nr_of_buckets;

	if (ctrl->type < V4L2_CTRL_COMPOUND_TYPES && id != class_ctrl &&
	    find_ref(hdl, class_ctrl) == NULL)
		if (!rtsv_ctrl_new_std(hdl, NULL, class_ctrl, 0, 0, 0, 0, NULL))
			return hdl->error;

	if (hdl->error)
		return hdl->error;

	if (!isp_calloc_item(new_ref))
		return handler_set_err(hdl, -RTS_ISP_ENOMEM);
	new_ref->ctrl = ctrl;
	if (ctrl->handler == hdl) {
		/*
		 * By default each control starts in a cluster of its own.
		 * new_ref->ctrl is basically a cluster array with one
		 * element, so that's perfect to use as the cluster pointer.
		 * But only do this for the handler that owns the control.
		 */
		ctrl->cluster = &new_ref->ctrl;
		ctrl->ncontrols = 1;
	}

	list_init(&new_ref->list);

	if (isp_list_empty(&hdl->ctrl_refs) || id > node2id(hdl->ctrl_refs.prev)) {
		list_insert_tail(&hdl->ctrl_refs, &new_ref->list);
		goto insert_in_hash;
	}

	list_foreach_data(ref, &hdl->ctrl_refs, list) {
		if (ref->ctrl->id < id)
			continue;
		if (ref->ctrl->id == id) {
			isp_free(new_ref);
			return 0;
		}
		list_insert_before(&ref->list, &new_ref->list);
		break;
	}

insert_in_hash:
	new_ref->next = hdl->buckets[bucket];
	hdl->buckets[bucket] = new_ref;
	return 0;
}

static struct v4l2_ctrl *
rtsv_ctrl_new(struct v4l2_ctrl_handler *hdl, const struct v4l2_ctrl_ops *ops,
	      const struct v4l2_ctrl_type_ops *type_ops, uint32_t id,
	      const char *name, enum v4l2_ctrl_type type, int64_t min,
	      int64_t max, uint64_t step, int64_t def,
	      const uint32_t dims[V4L2_CTRL_MAX_DIMS], uint32_t elem_size,
	      uint32_t flags, const char * const *qmenu,
	      const int64_t *qmenu_int, void *priv)
{
	struct v4l2_ctrl *ctrl;
	unsigned int sz_extra;
	unsigned int nr_of_dims = 0;
	unsigned int elems = 1;
	int is_array;
	unsigned int tot_ctrl_size;
	unsigned int idx;
	void *data;
	int err;

	if (hdl->error)
		return NULL;

	while (dims && dims[nr_of_dims]) {
		elems *= dims[nr_of_dims];
		nr_of_dims++;
		if (nr_of_dims == V4L2_CTRL_MAX_DIMS)
			break;
	}
	is_array = nr_of_dims > 0;

	switch (type) {
	case V4L2_CTRL_TYPE_INTEGER64:
		elem_size = sizeof(int64_t);
		break;
	case V4L2_CTRL_TYPE_STRING:
		elem_size = max + 1;
		break;
	case V4L2_CTRL_TYPE_U8:
		elem_size = sizeof(uint8_t);
		break;
	case V4L2_CTRL_TYPE_U16:
		elem_size = sizeof(uint16_t);
		break;
	case V4L2_CTRL_TYPE_U32:
		elem_size = sizeof(uint32_t);
		break;
	default:
		if (type < V4L2_CTRL_COMPOUND_TYPES)
			elem_size = sizeof(int32_t);
		break;
	}
	tot_ctrl_size = elem_size * elems;

	if (id == 0 || name == NULL || !elem_size ||
	    id >= V4L2_CID_PRIVATE_BASE ||
	    (type == V4L2_CTRL_TYPE_MENU && qmenu == NULL) ||
	    (type == V4L2_CTRL_TYPE_INTEGER_MENU && qmenu_int == NULL)) {
		handler_set_err(hdl, -RTS_ISP_ERANGE);
		return NULL;
	}
	err = check_range(type, min, max, step, def);
	if (err) {
		handler_set_err(hdl, err);
		return NULL;
	}
	if (is_array &&
	    (type == V4L2_CTRL_TYPE_BUTTON ||
	     type == V4L2_CTRL_TYPE_CTRL_CLASS)) {
		handler_set_err(hdl, -RTS_ISP_EINVAL);
		return NULL;
	}

	sz_extra = 0;
	if (type == V4L2_CTRL_TYPE_BUTTON)
		flags |= V4L2_CTRL_FLAG_WRITE_ONLY |
			V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
	else if (type == V4L2_CTRL_TYPE_CTRL_CLASS)
		flags |= V4L2_CTRL_FLAG_READ_ONLY;
	else if (type == V4L2_CTRL_TYPE_INTEGER64 ||
		 type == V4L2_CTRL_TYPE_STRING ||
		 type >= V4L2_CTRL_COMPOUND_TYPES ||
		 is_array)
		sz_extra += 2 * tot_ctrl_size;

	ctrl = isp_calloc(1, sizeof(*ctrl) + sz_extra);
	if (ctrl == NULL) {
		handler_set_err(hdl, -RTS_ISP_ENOMEM);
		return NULL;
	}

	list_init(&ctrl->list);
	ctrl->handler = hdl;
	ctrl->ops = ops;
	ctrl->type_ops = type_ops ? type_ops : &std_type_ops;
	ctrl->id = id;
	ctrl->name = name;
	ctrl->type = type;
	ctrl->flags = flags;
	ctrl->minimum = min;
	ctrl->maximum = max;
	ctrl->step = step;
	ctrl->default_value = def;
	ctrl->is_string = !is_array && type == V4L2_CTRL_TYPE_STRING;
	ctrl->is_ptr = (is_array || type >= V4L2_CTRL_COMPOUND_TYPES ||
			ctrl->is_string);
	ctrl->is_int = !ctrl->is_ptr && type != V4L2_CTRL_TYPE_INTEGER64;
	ctrl->is_array = is_array;
	ctrl->elems = elems;
	ctrl->nr_of_dims = nr_of_dims;
	if (nr_of_dims)
		isp_memcpy(ctrl->dims, dims, nr_of_dims * sizeof(dims[0]));
	ctrl->elem_size = elem_size;
	if (type == V4L2_CTRL_TYPE_MENU)
		ctrl->qmenu = qmenu;
	else if (type == V4L2_CTRL_TYPE_INTEGER_MENU)
		ctrl->qmenu_int = qmenu_int;
	ctrl->priv = priv;
	ctrl->cur.val = ctrl->val = def;
	data = &ctrl[1];

	if (!ctrl->is_int) {
		ctrl->p_new.p = data;
		ctrl->p_cur.p = (void *)((u32)data + tot_ctrl_size);
	} else {
		ctrl->p_new.p = &ctrl->val;
		ctrl->p_cur.p = &ctrl->cur.val;
	}
	for (idx = 0; idx < elems; idx++) {
		ctrl->type_ops->init(ctrl, idx, ctrl->p_cur);
		ctrl->type_ops->init(ctrl, idx, ctrl->p_new);
	}

	if (handler_new_ref(hdl, ctrl)) {
		isp_free(ctrl);
		return NULL;
	}
	list_insert_tail(&hdl->ctrls, &ctrl->list);
	return ctrl;
}

struct v4l2_ctrl *rtsv_ctrl_new_custom(struct v4l2_ctrl_handler *hdl,
				       const struct v4l2_ctrl_config *cfg,
				       void *priv)
{
	int is_menu;
	struct v4l2_ctrl *ctrl;
	const char *name = cfg->name;
	const char * const *qmenu = cfg->qmenu;
	const int64_t *qmenu_int = cfg->qmenu_int;
	enum v4l2_ctrl_type type = cfg->type;
	uint32_t flags = cfg->flags;
	int64_t min = cfg->min;
	int64_t max = cfg->max;
	uint64_t step = cfg->step;
	int64_t def = cfg->def;

	if (name == NULL)
		rtsv_ctrl_fill(cfg->id, &name, &type, &min, &max, &step,
			       &def, &flags);

	is_menu = (cfg->type == V4L2_CTRL_TYPE_MENU ||
		   cfg->type == V4L2_CTRL_TYPE_INTEGER_MENU);
	if (is_menu)
		isp_assert(!step);
	else
		isp_assert(!cfg->menu_skip_mask);
	if (cfg->type == V4L2_CTRL_TYPE_MENU && qmenu == NULL)
		qmenu = rtsv_ctrl_get_menu(cfg->id);
	else if (cfg->type == V4L2_CTRL_TYPE_INTEGER_MENU &&
		 qmenu_int == NULL) {
		handler_set_err(hdl, -RTS_ISP_EINVAL);
		return NULL;
	}

	ctrl = rtsv_ctrl_new(hdl, cfg->ops, cfg->type_ops, cfg->id, name,
			     type, min, max,
			     is_menu ? cfg->menu_skip_mask : step, def,
			     cfg->dims, cfg->elem_size,
			     flags, qmenu, qmenu_int, priv);
	return ctrl;
}

struct v4l2_ctrl *rtsv_ctrl_new_std(struct v4l2_ctrl_handler *hdl,
				    const struct v4l2_ctrl_ops *ops,
				    uint32_t id, int64_t min, int64_t max,
				    uint64_t step, int64_t def, void *priv)
{
	const char *name;
	enum v4l2_ctrl_type type;
	uint32_t flags;

	rtsv_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);
	if (type == V4L2_CTRL_TYPE_MENU ||
	    type == V4L2_CTRL_TYPE_INTEGER_MENU ||
	    type >= V4L2_CTRL_COMPOUND_TYPES) {
		handler_set_err(hdl, -RTS_ISP_EINVAL);
		return NULL;
	}
	return rtsv_ctrl_new(hdl, ops, NULL, id, name, type,
			     min, max, step, def, NULL, 0,
			     flags, NULL, NULL, priv);
}

struct v4l2_ctrl *rtsv_ctrl_new_std_menu(struct v4l2_ctrl_handler *hdl,
					 const struct v4l2_ctrl_ops *ops,
					 uint32_t id, uint8_t _max,
					 uint64_t mask, uint8_t _def,
					 void *priv)
{
	const char * const *qmenu = NULL;
	const int64_t *qmenu_int = NULL;
	unsigned int qmenu_int_len = 0;
	const char *name;
	enum v4l2_ctrl_type type;
	int64_t min;
	int64_t max = _max;
	int64_t def = _def;
	uint64_t step;
	uint32_t flags;

	rtsv_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);

	if (type == V4L2_CTRL_TYPE_MENU)
		qmenu = rtsv_ctrl_get_menu(id);

	if ((!qmenu && !qmenu_int) || (qmenu_int && max > qmenu_int_len)) {
		handler_set_err(hdl, -RTS_ISP_EINVAL);
		return NULL;
	}
	return rtsv_ctrl_new(hdl, ops, NULL, id, name, type,
			     0, max, mask, def, NULL, 0,
			     flags, qmenu, qmenu_int, priv);
}

struct v4l2_ctrl *rtsv_ctrl_new_std_menu_items(struct v4l2_ctrl_handler *hdl,
					       const struct v4l2_ctrl_ops *ops,
					       uint32_t id, uint8_t _max,
					       uint64_t mask, uint8_t _def,
					       const char * const *qmenu,
					       void *priv)
{
	enum v4l2_ctrl_type type;
	const char *name;
	uint32_t flags;
	uint64_t step;
	int64_t min;
	int64_t max = _max;
	int64_t def = _def;

	/*
	 * v4l2_ctrl_new_std_menu_items() should only be called for
	 * standard controls without a standard menu.
	 */
	if (rtsv_ctrl_get_menu(id)) {
		handler_set_err(hdl, -RTS_ISP_EINVAL);
		return NULL;
	}

	rtsv_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);
	if (type != V4L2_CTRL_TYPE_MENU || qmenu == NULL) {
		handler_set_err(hdl, -RTS_ISP_EINVAL);
		return NULL;
	}
	return rtsv_ctrl_new(hdl, ops, NULL, id, name, type,
			     0, max, mask, def, NULL, 0,
			     flags, qmenu, NULL, priv);

}

struct v4l2_ctrl *rtsv_ctrl_new_int_menu(struct v4l2_ctrl_handler *hdl,
					 const struct v4l2_ctrl_ops *ops,
					 uint32_t id, uint8_t _max,
					 uint8_t _def, const int64_t *qmenu_int,
					 void *priv)
{
	const char *name;
	enum v4l2_ctrl_type type;
	int64_t min;
	uint64_t step;
	int64_t max = _max;
	int64_t def = _def;
	uint32_t flags;

	rtsv_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);
	if (type != V4L2_CTRL_TYPE_INTEGER_MENU) {
		handler_set_err(hdl, -RTS_ISP_EINVAL);
		return NULL;
	}
	return rtsv_ctrl_new(hdl, ops, NULL, id, name, type,
			     0, max, 0, def, NULL, 0,
			     flags, NULL, qmenu_int, priv);
}

void rtsv_ctrl_cluster(unsigned int ncontrols, struct v4l2_ctrl **controls)
{
	int has_volatiles = RTS_ISP_FALSE;
	int i;

	isp_assert(ncontrols);
	isp_assert(controls[0]);

	if (ncontrols == 0 || controls[0] == NULL)
		return;

	for (i = 0; i < (int)ncontrols; i++) {
		if (controls[i]) {
			controls[i]->cluster = controls;
			controls[i]->ncontrols = ncontrols;
			if (controls[i]->flags & V4L2_CTRL_FLAG_VOLATILE)
				has_volatiles = RTS_ISP_TRUE;
		}
	}
	controls[0]->has_volatiles = has_volatiles;
}

void rtsv_ctrl_auto_cluster(unsigned int ncontrols, struct v4l2_ctrl **controls,
			    uint8_t manual_val, int set_volatile)
{
	struct v4l2_ctrl *master = controls[0];
	uint32_t flag = 0;
	int i;

	rtsv_ctrl_cluster(ncontrols, controls);
	isp_assert(ncontrols > 1);
	isp_assert(manual_val >= master->minimum);
	isp_assert(manual_val <= master->maximum);
	if (set_volatile)
		isp_assert(has_op(master, g_volatile_ctrl));
	master->is_auto = RTS_ISP_TRUE;
	master->has_volatiles = set_volatile;
	master->manual_mode_value = manual_val;
	master->flags |= V4L2_CTRL_FLAG_UPDATE;

	if (!is_cur_manual(master))
		flag = (V4L2_CTRL_FLAG_INACTIVE |
			(set_volatile ? V4L2_CTRL_FLAG_VOLATILE : 0));

	for (i = 1; i < (int)ncontrols; i++)
		if (controls[i])
			controls[i]->flags |= flag;
}

void rtsv_ctrl_activate(struct v4l2_ctrl *ctrl, int active)
{
	if (ctrl == NULL)
		return;

	if (active)
		/* clear V4L2_CTRL_FLAG_INACTIVE */
		isp_clr_bit(ctrl->flags, 4);
	else
		/* set V4L2_CTRL_FLAG_INACTIVE */
		isp_set_bit(ctrl->flags, 4);
}

void rtsv_ctrl_grab(struct v4l2_ctrl *ctrl, int grabbed)
{
	if (ctrl == NULL)
		return;

	if (grabbed)
		/* set V4L2_CTRL_FLAG_GRABBED */
		isp_set_bit(ctrl->flags, 1);
	else
		/* clear V4L2_CTRL_FLAG_GRABBED */
		isp_clr_bit(ctrl->flags, 1);
}

static void log_ctrl(const struct v4l2_ctrl *ctrl,
		     const char *prefix, const char *colon)
{
	if (ctrl->flags & (V4L2_CTRL_FLAG_DISABLED | V4L2_CTRL_FLAG_WRITE_ONLY))
		return;
	if (ctrl->type == V4L2_CTRL_TYPE_CTRL_CLASS)
		return;

	isp_info_cont("%s%s%s: ", prefix, colon, ctrl->name);

	ctrl->type_ops->log(ctrl);

	if (ctrl->flags & (V4L2_CTRL_FLAG_INACTIVE |
			   V4L2_CTRL_FLAG_GRABBED |
			   V4L2_CTRL_FLAG_VOLATILE)) {
		if (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
			isp_info_cont(" inactive");
		if (ctrl->flags & V4L2_CTRL_FLAG_GRABBED)
			isp_info_cont(" grabbed");
		if (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE)
			isp_info_cont(" volatile");
	}
	isp_info_cont("\n");
}

void rtsv_ctrl_handler_log_status(struct v4l2_ctrl_handler *hdl,
				  const char *prefix)
{
	struct v4l2_ctrl *ctrl;
	const char *colon = "";
	int len;

	if (hdl == NULL)
		return;
	if (prefix == NULL)
		prefix = "";
	len = strlen(prefix);
	if (len && prefix[len - 1] != ' ')
		colon = ": ";
	list_foreach_data(ctrl, &hdl->ctrls, list)
		if (!(ctrl->flags & V4L2_CTRL_FLAG_DISABLED))
			log_ctrl(ctrl, prefix, colon);
}

int rtsv_ctrl_handler_setup(struct v4l2_ctrl_handler *hdl)
{
	struct v4l2_ctrl *ctrl;
	int ret = 0;

	if (hdl == NULL)
		return 0;

	list_foreach_data(ctrl, &hdl->ctrls, list)
		ctrl->done = RTS_ISP_FALSE;

	list_foreach_data(ctrl, &hdl->ctrls, list) {
		struct v4l2_ctrl *master = ctrl->cluster[0];
		int i;

		/* Skip if this control was already handled by a cluster. */
		/* Skip button controls and read-only controls. */
		if (ctrl->done || ctrl->type == V4L2_CTRL_TYPE_BUTTON ||
		    (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY))
			continue;

		for (i = 0; i < (int)master->ncontrols; i++) {
			if (master->cluster[i]) {
				cur_to_new(master->cluster[i]);
				master->cluster[i]->is_new = 1;
				master->cluster[i]->done = RTS_ISP_TRUE;
			}
		}
		ret = call_op(master, s_ctrl);
		if (ret) {
			isp_error("%s %s s_ctrl %d \r\n", __func__, master->name, ret);
			break;
		}

	}

	return ret;
}

void rtsv_ctrl_handler_backup_auto(struct v4l2_ctrl_handler *hdl)
{
	struct v4l2_ctrl *ctrl;

	if (hdl == NULL)
		return;

	list_foreach_data(ctrl, &hdl->ctrls, list) {
		struct v4l2_ctrl *master = ctrl->cluster[0];

		if (ctrl == master && master->is_auto &&
		    master->has_volatiles && !is_cur_manual(master)) {
			int i;

			for (i = 1; i < (int)master->ncontrols; i++)
				cur_to_new(master->cluster[i]);
			if (!call_op(master, g_volatile_ctrl))
				for (i = 1; i < (int)master->ncontrols; i++)
					new_to_cur(master->cluster[i],
						   RTS_ISP_TRUE);
		}
	}
}

int rtsv_query_ext_ctrl(struct v4l2_ctrl_handler *hdl,
			struct v4l2_query_ext_ctrl *qc)
{
	const unsigned int next_flags = (V4L2_CTRL_FLAG_NEXT_CTRL |
					 V4L2_CTRL_FLAG_NEXT_COMPOUND);
	uint32_t id = qc->id & V4L2_CTRL_ID_MASK;
	struct v4l2_ctrl_ref *ref;
	struct v4l2_ctrl *ctrl;

	if (hdl == NULL)
		return -RTS_ISP_EINVAL;

	ref = find_ref(hdl, id);

	if ((qc->id & next_flags) && !isp_list_empty(&hdl->ctrl_refs)) {
		int is_compound;
		/* Match any control that is not hidden */
		int mask = 1;
		int match = RTS_ISP_FALSE;

		if ((qc->id & next_flags) == V4L2_CTRL_FLAG_NEXT_COMPOUND) {
			/* Match any hidden control */
			match = RTS_ISP_TRUE;
		} else if ((qc->id & next_flags) == next_flags) {
			/* Match any control, compound or not */
			mask = 0;
		}

		/* Find the next control with ID > qc->id */
		/* Did we reach the end of the control list? */
		if (id >= node2id(hdl->ctrl_refs.prev)) {
			ref = NULL; /* Yes, so there is no next control */
		} else if (ref) {
			struct v4l2_ctrl_ref *cur_ref = ref;
			/*
			 * We found a control with the given ID, so just get
			 * the next valid one in the list.
			 */
			list_foreach_data(ref, &cur_ref->list, list) {
				if (&ref->list == &hdl->ctrl_refs)
					break;
				is_compound = (ref->ctrl->is_array ||
					       ref->ctrl->type >=
					       V4L2_CTRL_COMPOUND_TYPES);
				if (id < ref->ctrl->id &&
				    (is_compound & mask) == match)
					break;
			}
			if (&ref->list == &hdl->ctrl_refs)
				ref = NULL;
		} else {
			/*
			 * No control with the given ID exists, so start
			 * searching for the next largest ID. We know there
			 * is one, otherwise the first 'if' above would have
			 * been RTS_ISP_TRUE.
			 */
			list_foreach_data(ref, &hdl->ctrl_refs, list) {
				is_compound = (ref->ctrl->is_array ||
					       ref->ctrl->type >=
					       V4L2_CTRL_COMPOUND_TYPES);
				if (id < ref->ctrl->id &&
				    (is_compound & mask) == match)
					break;
			}
			if (&ref->list == &hdl->ctrl_refs)
				ref = NULL;
		}
	}

	if (!ref)
		return -RTS_ISP_EINVAL;

	ctrl = ref->ctrl;
	memset(qc, 0, sizeof(*qc));
	if (id >= V4L2_CID_PRIVATE_BASE)
		qc->id = id;
	else
		qc->id = ctrl->id;
	isp_strlcpy(qc->name, ctrl->name, sizeof(qc->name));
	qc->flags = user_flags(ctrl);
	qc->type = ctrl->type;
	qc->elem_size = ctrl->elem_size;
	qc->elems = ctrl->elems;
	qc->nr_of_dims = ctrl->nr_of_dims;
	isp_memcpy(qc->dims, ctrl->dims, qc->nr_of_dims * sizeof(qc->dims[0]));
	qc->minimum = ctrl->minimum;
	qc->maximum = ctrl->maximum;
	qc->default_value = ctrl->default_value;
	if (ctrl->type == V4L2_CTRL_TYPE_MENU
	    || ctrl->type == V4L2_CTRL_TYPE_INTEGER_MENU)
		qc->step = 1;
	else
		qc->step = ctrl->step;
	return 0;
}

int rtsv_queryctrl(struct v4l2_ctrl_handler *hdl, struct v4l2_queryctrl *qc)
{
	struct v4l2_query_ext_ctrl qec;
	int rc;

	qec.id = qc->id;
	rc = rtsv_query_ext_ctrl(hdl, &qec);
	if (rc)
		return rc;

	qc->id = qec.id;
	qc->type = qec.type;
	qc->flags = qec.flags;
	isp_strlcpy((char *)qc->name, qec.name, sizeof(qc->name));
	switch (qc->type) {
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
	case V4L2_CTRL_TYPE_STRING:
	case V4L2_CTRL_TYPE_BITMASK:
		qc->minimum = qec.minimum;
		qc->maximum = qec.maximum;
		qc->step = qec.step;
		qc->default_value = qec.default_value;
		break;
	default:
		qc->minimum = 0;
		qc->maximum = 0;
		qc->step = 0;
		qc->default_value = 0;
		break;
	}
	return 0;
}

int rtsv_querymenu(struct v4l2_ctrl_handler *hdl, struct v4l2_querymenu *qm)
{
	struct v4l2_ctrl *ctrl;
	int i = qm->index;

	ctrl = rtsv_ctrl_find(hdl, qm->id);
	if (!ctrl)
		return -RTS_ISP_EINVAL;

	qm->reserved = 0;
	/* Sanity checks */
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_MENU:
		if (ctrl->qmenu == NULL)
			return -RTS_ISP_EINVAL;
		break;
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		if (ctrl->qmenu_int == NULL)
			return -RTS_ISP_EINVAL;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	if (i < ctrl->minimum || i > ctrl->maximum)
		return -RTS_ISP_EINVAL;

	/* Use mask to see if this menu item should be skipped */
	if (ctrl->menu_skip_mask & ((uint64_t)1 << i))
		return -RTS_ISP_EINVAL;
	/* Empty menu items should also be skipped */
	if (ctrl->type == V4L2_CTRL_TYPE_MENU) {
		if (ctrl->qmenu[i] == NULL || ctrl->qmenu[i][0] == '\0')
			return -RTS_ISP_EINVAL;
		isp_strlcpy((char *)qm->name, ctrl->qmenu[i], sizeof(qm->name));
	} else {
		qm->value = ctrl->qmenu_int[i];
	}
	return 0;
}

static int prepare_ext_ctrls(struct v4l2_ctrl_handler *hdl,
			     struct v4l2_ext_controls *cs,
			     struct v4l2_ctrl_helper *helpers,
			     int get)
{
	struct v4l2_ctrl_helper *h;
	int have_clusters = RTS_ISP_FALSE;
	int i;

	for (i = 0, h = helpers; i < (int)cs->count; i++, h++) {
		struct v4l2_ext_control *c = &cs->controls[i];
		struct v4l2_ctrl_ref *ref;
		struct v4l2_ctrl *ctrl;
		uint32_t id = c->id & V4L2_CTRL_ID_MASK;

		cs->error_idx = i;

		if (cs->which &&
		    cs->which != V4L2_CTRL_WHICH_DEF_VAL &&
		    V4L2_CTRL_ID2WHICH(id) != cs->which)
			return -RTS_ISP_EINVAL;

		if (id >= V4L2_CID_PRIVATE_BASE)
			return -RTS_ISP_EINVAL;
		ref = find_ref(hdl, id);
		if (ref == NULL)
			return -RTS_ISP_EINVAL;
		ctrl = ref->ctrl;
		if (ctrl->flags & V4L2_CTRL_FLAG_DISABLED)
			return -RTS_ISP_EINVAL;

		if (ctrl->cluster[0]->ncontrols > 1)
			have_clusters = RTS_ISP_TRUE;
		if (ctrl->cluster[0] != ctrl)
			ref = find_ref(hdl, ctrl->cluster[0]->id);
		if (ctrl->is_ptr && !ctrl->is_string) {
			unsigned int tot_size = ctrl->elems * ctrl->elem_size;

			if (c->size < tot_size) {
				if (get) {
					c->size = tot_size;
					return -RTS_ISP_ENOSPC;
				}
				return -RTS_ISP_EFAULT;
			}
			c->size = tot_size;
		}
		/* Store the ref to the master control of the cluster */
		h->mref = ref;
		h->ctrl = ctrl;
		/*
		 * Initially set next to 0, meaning that there is no other
		 * control in this helper array belonging to the same cluster
		 */
		h->next = 0;
	}

	/*
	 * We are done if there were no controls that belong to a multi-
	 * control cluster.
	 */
	if (!have_clusters)
		return 0;

	/*
	 * The code below figures out in O(n) time which controls in the list
	 * belong to the same cluster.
	 */

	/* First zero the helper field in the master control references */
	for (i = 0; i < (int)cs->count; i++)
		helpers[i].mref->helper = NULL;
	for (i = 0, h = helpers; i < (int)cs->count; i++, h++) {
		struct v4l2_ctrl_ref *mref = h->mref;

		/*
		 * If the mref->helper is set, then it points to an earlier
		 * that belongs to the same cluster.
		 */
		if (mref->helper) {
			/*
			 * Set the next field of mref->helper to the current
			 * index: this means that that earlier helper now
			 * points to the next helper in the same cluster.
			 */
			mref->helper->next = i;
			/*
			 * mref should be set only for the first helper in the
			 * cluster, clear the others.
			 */
			h->mref = NULL;
		}
		/* Point the mref helper to the current helper struct. */
		mref->helper = h;
	}
	return 0;
}

/*
 * Handles the corner case where cs->count == 0. It checks whether the
 * specified control class exists. If that class ID is 0, then it checks
 * whether there are any controls at all.
 */
static int class_check(struct v4l2_ctrl_handler *hdl, uint32_t which)
{
	if (which == 0 || which == V4L2_CTRL_WHICH_DEF_VAL)
		return 0;
	return find_ref(hdl, which | 1) ? 0 : -RTS_ISP_EINVAL;
}



int rtsv_g_ext_ctrls(struct v4l2_ctrl_handler *hdl,
		     struct v4l2_ext_controls *cs)
{
	struct v4l2_ctrl_helper helper[4];
	struct v4l2_ctrl_helper *helpers = helper;
	int ret;
	int i, j;
	int def_value;

	def_value = (cs->which == V4L2_CTRL_WHICH_DEF_VAL);

	cs->error_idx = cs->count;
	cs->which = V4L2_CTRL_ID2WHICH(cs->which);

	if (hdl == NULL)
		return -RTS_ISP_EINVAL;

	if (cs->count == 0)
		return class_check(hdl, cs->which);

	if (cs->count > ARRAY_SIZE(helper)) {
		if (!isp_calloc_array(helpers, cs->count))
			return -RTS_ISP_ENOMEM;
	}

	ret = prepare_ext_ctrls(hdl, cs, helpers, RTS_ISP_TRUE);
	cs->error_idx = cs->count;

	for (i = 0; !ret && i < (int)cs->count; i++)
		if (helpers[i].ctrl->flags & V4L2_CTRL_FLAG_WRITE_ONLY)
			ret = -RTS_ISP_EACCES;

	for (i = 0; !ret && i < (int)cs->count; i++) {
		int (*ctrl_to_user)(struct v4l2_ext_control *c,
				    struct v4l2_ctrl *ctrl);
		struct v4l2_ctrl *master;

		ctrl_to_user = def_value ? def_to_user : cur_to_user;

		if (helpers[i].mref == NULL)
			continue;

		master = helpers[i].mref->ctrl;
		cs->error_idx = i;

		/* g_volatile_ctrl will update the new control values */
		if (!def_value &&
		    ((master->flags & V4L2_CTRL_FLAG_VOLATILE) ||
		     (master->has_volatiles && !is_cur_manual(master)))) {
			for (j = 0; j < (int)master->ncontrols; j++)
				cur_to_new(master->cluster[j]);
			ret = call_op(master, g_volatile_ctrl);
			ctrl_to_user = new_to_user;
		}
		/*
		 * If OK, then copy the current (for non-volatile controls) or
		 * the new (for volatile controls) control values to the caller
		 */
		if (!ret) {
			uint32_t idx = i;

			do {
				ret = ctrl_to_user(cs->controls + idx,
						   helpers[idx].ctrl);
				idx = helpers[idx].next;
			} while (!ret && idx);
		}
	}

	if (cs->count > ARRAY_SIZE(helper))
		isp_free(helpers);
	return ret;
}

static int get_ctrl(struct v4l2_ctrl *ctrl, struct v4l2_ext_control *c)
{
	struct v4l2_ctrl *master = ctrl->cluster[0];
	int ret = 0;
	int i;

	/* Compound controls are not supported. The new_to_user() and
	 * cur_to_user() calls below would need to be modified not to access
	 * userspace memory when called from get_ctrl().
	 */
	if (!ctrl->is_int && ctrl->type != V4L2_CTRL_TYPE_INTEGER64)
		return -RTS_ISP_EINVAL;

	if (ctrl->flags & V4L2_CTRL_FLAG_WRITE_ONLY)
		return -RTS_ISP_EACCES;

	/* g_volatile_ctrl will update the current control values */
	if (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE) {
		for (i = 0; i < (int)master->ncontrols; i++)
			cur_to_new(master->cluster[i]);
		ret = call_op(master, g_volatile_ctrl);
		new_to_user(c, ctrl);
	} else {
		cur_to_user(c, ctrl);
	}
	return ret;
}

int rtsv_g_ctrl(struct v4l2_ctrl_handler *hdl, struct v4l2_control *control)
{
	struct v4l2_ctrl *ctrl = rtsv_ctrl_find(hdl, control->id);
	struct v4l2_ext_control c;
	int ret;

	if (ctrl == NULL || !ctrl->is_int)
		return -RTS_ISP_EINVAL;
	ret = get_ctrl(ctrl, &c);
	control->value = c.value;
	return ret;
}

int32_t rtsv_ctrl_g_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_ext_control c;

	isp_assert(ctrl->is_int);
	c.value = 0;
	get_ctrl(ctrl, &c);
	return c.value;
}

int64_t rtsv_ctrl_g_ctrl_int64(struct v4l2_ctrl *ctrl)
{
	struct v4l2_ext_control c;

	isp_assert(!ctrl->is_ptr);
	isp_assert(ctrl->type == V4L2_CTRL_TYPE_INTEGER64);
	c.value64 = 0;
	get_ctrl(ctrl, &c);
	return c.value64;
}


static int try_or_set_cluster(struct v4l2_ctrl *master, int set)
{
	int ret;
	int i;
	int update_flag;

	/*
	 * Go through the cluster and either validate the new value or
	 * (if no new value was set), copy the current value to the new
	 * value, ensuring a consistent view for the control ops when called.
	 */
	for (i = 0; i < (int)master->ncontrols; i++) {
		struct v4l2_ctrl *ctrl = master->cluster[i];

		if (ctrl == NULL)
			continue;

		if (master->handler->setting)
			ctrl->modified = RTS_ISP_TRUE;

		if (!ctrl->is_new) {
			cur_to_new(ctrl);
			continue;
		}
		if (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED))
			return -RTS_ISP_EBUSY;
	}

	ret = call_op(master, try_ctrl);

	/* Don't set if there is no change */
	if (ret || !set || !cluster_changed(master))
		return ret;
	ret = call_op(master, s_ctrl);
	if (ret)
		return ret;

	update_flag = is_cur_manual(master) != is_new_manual(master);
	/* If OK, then make the new values permanent. */
	for (i = 0; i < (int)master->ncontrols; i++) {
		new_to_cur(master->cluster[i], update_flag);
		if (update_flag && i > 0) {
			struct v4l2_ctrl *ctrl = master->cluster[i];

			ctrl->flags &= ~(V4L2_CTRL_FLAG_INACTIVE |
					 V4L2_CTRL_FLAG_VOLATILE);
			if (!is_cur_manual(master)) {
				ctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
				if (ctrl->cluster[0]->has_volatiles)
					ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

			}

		}
	}
	return 0;
}

static int validate_ctrls(struct v4l2_ext_controls *cs,
			  struct v4l2_ctrl_helper *helpers, int set)
{
	unsigned int i;
	int ret = 0;

	cs->error_idx = cs->count;
	for (i = 0; i < cs->count; i++) {
		struct v4l2_ctrl *ctrl = helpers[i].ctrl;
		union v4l2_ctrl_ptr p_new;

		cs->error_idx = i;

		if (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY)
			return -RTS_ISP_EACCES;
		if (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED))
			return -RTS_ISP_EBUSY;
		/*
		 * Skip validation for now if the payload needs to be copied,
		 * We'll validate those later.
		 */
		if (ctrl->is_ptr)
			continue;
		if (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
			p_new.p_s64 = (int64_t *)&cs->controls[i].value64;
		else
			p_new.p_s32 = (int32_t *)&cs->controls[i].value;
		ret = validate_new(ctrl, p_new);
		if (ret)
			return ret;
	}
	return 0;
}

static void update_from_auto_cluster(struct v4l2_ctrl *master)
{
	int i;

	for (i = 1; i < (int)master->ncontrols; i++)
		cur_to_new(master->cluster[i]);
	if (!call_op(master, g_volatile_ctrl))
		for (i = 1; i < (int)master->ncontrols; i++)
			if (master->cluster[i])
				master->cluster[i]->is_new = 1;
}

static int try_set_ext_ctrls(struct v4l2_ctrl_handler *hdl,
			     struct v4l2_ext_controls *cs, int set)
{
	struct v4l2_ctrl_helper helper[4];
	struct v4l2_ctrl_helper *helpers = helper;
	unsigned int i, j;
	int ret;

	cs->error_idx = cs->count;

	if (cs->which == V4L2_CTRL_WHICH_DEF_VAL)
		return -RTS_ISP_EINVAL;

	cs->which = V4L2_CTRL_ID2WHICH(cs->which);

	if (hdl == NULL)
		return -RTS_ISP_EINVAL;

	if (cs->count == 0)
		return class_check(hdl, cs->which);

	if (cs->count > ARRAY_SIZE(helper)) {
		if (!isp_calloc_array(helpers, cs->count))
			return -RTS_ISP_ENOMEM;
	}
	ret = prepare_ext_ctrls(hdl, cs, helpers, RTS_ISP_FALSE);
	if (!ret)
		ret = validate_ctrls(cs, helpers, set);
	if (ret && set)
		cs->error_idx = cs->count;
	for (i = 0; !ret && i < cs->count; i++) {
		struct v4l2_ctrl *master;
		uint32_t idx = i;

		if (helpers[i].mref == NULL)
			continue;

		cs->error_idx = i;
		master = helpers[i].mref->ctrl;

		for (j = 0; j < master->ncontrols; j++)
			if (master->cluster[j])
				master->cluster[j]->is_new = 0;

		if (master->is_auto && master->has_volatiles &&
		    !is_cur_manual(master)) {
			/* Pick an initial non-manual value */
			int32_t new_auto_val = master->manual_mode_value + 1;
			uint32_t tmp_idx = idx;

			do {
				/*
				 * Check if the auto control is part of the
				 * list, and remember the new value.
				 */
				if (helpers[tmp_idx].ctrl == master)
					new_auto_val =
						cs->controls[tmp_idx].value;
				tmp_idx = helpers[tmp_idx].next;
			} while (tmp_idx);
			/*
			 * If the new value == the manual value, then copy
			 * the current volatile values.
			 */
			if (new_auto_val == master->manual_mode_value)
				update_from_auto_cluster(master);
		}

		/*
		 * Copy the new caller-supplied control values.
		 * user_to_new() sets 'is_new' to 1.
		 */
		do {
			struct v4l2_ctrl *ctrl = helpers[idx].ctrl;

			ret = user_to_new(cs->controls + idx, ctrl);
			if (!ret && ctrl->is_ptr)
				ret = validate_new(ctrl, ctrl->p_new);
			idx = helpers[idx].next;
		} while (!ret && idx);

		if (!ret)
			ret = try_or_set_cluster(master, set);

		if (!ret) {
			idx = i;
			do {
				ret = new_to_user(cs->controls + idx,
						  helpers[idx].ctrl);
				idx = helpers[idx].next;
			} while (!ret && idx);
		}
	}

	if (cs->count > ARRAY_SIZE(helper))
		isp_free(helpers);
	return ret;
}

int rtsv_try_ext_ctrls(struct v4l2_ctrl_handler *hdl,
		       struct v4l2_ext_controls *cs)
{
	return try_set_ext_ctrls(hdl, cs, RTS_ISP_FALSE);
}

int rtsv_s_ext_ctrls(struct v4l2_ctrl_handler *hdl,
		     struct v4l2_ext_controls *cs)
{
	int ret;

	hdl->setting = RTS_ISP_TRUE;
	ret = try_set_ext_ctrls(hdl, cs, RTS_ISP_TRUE);
	hdl->setting = RTS_ISP_FALSE;

	return ret;
}

static int __set_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_ctrl *master = ctrl->cluster[0];
	int ret;
	int i;

	/* Reset the 'is_new' flags of the cluster */
	for (i = 0; i < (int)master->ncontrols; i++)
		if (master->cluster[i])
			master->cluster[i]->is_new = 0;

	ret = validate_new(ctrl, ctrl->p_new);
	if (ret)
		return ret;

	/*
	 * For autoclusters with volatiles that are switched from auto to
	 * manual mode we have to update the current volatile values since
	 * those will become the initial manual values after such a switch.
	 */
	if (master->is_auto && master->has_volatiles && ctrl == master &&
	    !is_cur_manual(master) && ctrl->val == master->manual_mode_value)
		update_from_auto_cluster(master);

	ctrl->is_new = 1;
	return try_or_set_cluster(master, RTS_ISP_TRUE);
}

static int set_ctrl(struct v4l2_ctrl *ctrl, struct v4l2_ext_control *c)
{
	int ret;

	user_to_new(c, ctrl);
	ret = __set_ctrl(ctrl);
	if (!ret)
		cur_to_user(c, ctrl);
	return ret;
}

int rtsv_s_ctrl(struct v4l2_ctrl_handler *hdl, struct v4l2_control *control)
{
	struct v4l2_ctrl *ctrl = rtsv_ctrl_find(hdl, control->id);
	struct v4l2_ext_control c;
	int ret;

	if (ctrl == NULL || !ctrl->is_int)
		return -RTS_ISP_EINVAL;

	if (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY)
		return -RTS_ISP_EACCES;

	hdl->setting = RTS_ISP_TRUE;
	c.id = control->id;
	c.value = control->value;
	ret = set_ctrl(ctrl, &c);
	control->value = c.value;
	hdl->setting = RTS_ISP_FALSE;
	return ret;
}

int rtsv_ctrl_s_ctrl(struct v4l2_ctrl *ctrl, int32_t val)
{
	isp_assert(ctrl->is_int);
	ctrl->val = val;
	return __set_ctrl(ctrl);
}

int rtsv_ctrl_s_ctrl_int64(struct v4l2_ctrl *ctrl, int64_t val)
{
	isp_assert(!ctrl->is_ptr);
	isp_assert(ctrl->type == V4L2_CTRL_TYPE_INTEGER64);
	*ctrl->p_new.p_s64 = val;
	return __set_ctrl(ctrl);
}

int rtsv_ctrl_s_ctrl_string(struct v4l2_ctrl *ctrl, const char *s)
{
	isp_assert(ctrl->type == V4L2_CTRL_TYPE_STRING);
	isp_strlcpy(ctrl->p_new.p_char, s, ctrl->maximum + 1);
	return __set_ctrl(ctrl);
}

int rtsv_ctrl_modify_range(struct v4l2_ctrl *ctrl, int64_t min, int64_t max,
			   uint64_t step, int64_t def)
{
	int value_changed;
	int ret;

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_INTEGER64:
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
	case V4L2_CTRL_TYPE_BITMASK:
	case V4L2_CTRL_TYPE_U8:
	case V4L2_CTRL_TYPE_U16:
	case V4L2_CTRL_TYPE_U32:
		if (ctrl->is_array)
			return -RTS_ISP_EINVAL;
		ret = check_range(ctrl->type, min, max, step, def);
		if (ret)
			return ret;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	if ((ctrl->minimum != min) || (ctrl->maximum != max) ||
	    (ctrl->step != step) || ctrl->default_value != def) {
		ctrl->minimum = min;
		ctrl->maximum = max;
		ctrl->step = step;
		ctrl->default_value = def;
	}
	cur_to_new(ctrl);
	if (validate_new(ctrl, ctrl->p_new)) {
		if (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
			*ctrl->p_new.p_s64 = def;
		else
			*ctrl->p_new.p_s32 = def;
	}

	if (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
		value_changed = *ctrl->p_new.p_s64 != *ctrl->p_cur.p_s64;
	else
		value_changed = *ctrl->p_new.p_s32 != *ctrl->p_cur.p_s32;
	if (value_changed)
		ret = __set_ctrl(ctrl);
	return ret;
}

