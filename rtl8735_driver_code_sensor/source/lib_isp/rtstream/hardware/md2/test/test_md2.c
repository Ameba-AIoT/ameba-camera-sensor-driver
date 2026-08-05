/*
 * Realtek Semiconductor Corp.
 *
 * example/example_md2.c
 *
 * Copyright (C) 2019      Anakin Wang<anakin_wang@realsil.com.cn>
 */

#if 1
#include <cmsis_os.h>
#include "cmsis_os2.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "rt_types.h"
#include "rt_task.h"

#include <rtscamkit.h>
#include <rtsvideo.h>



/* code flow

+-----------+     +-----------+     +-----------+     +-------------+
|           |     |           |     |           |     |             |
| rts_av_   |     | rts_av_   |     | rts_av_   |     | rts_av_get  |
| query_md2 |====>| set_md2   |====>| poll_md2  |====>| _md2_result |
|           |     |           |     |           |     |(motion_map) |
+-----------+     +-----------+     +-----------+     |(or res bmp) |
                                                      +-------------+
*/


struct rts_md2_attr g_attr={0};
struct rts_md2_ctrl g_ctrl = {
	.sensitivity = -1,
};

#if 0
static int __parse_args(int argc, char *argv[])
{
	int opt;

	g_attr.sample.x = 0;
	g_attr.sample.y = 0;
	g_attr.sample.w = 320;
	g_attr.sample.h = 240;
	g_attr.sample.scale_x = 2;
	g_attr.sample.scale_y = 2;

	g_attr.bin_bits = 0;
	g_attr.nr_bins = 0;

	optind = 0;  //thread need reset global vars of getopt_long()
	while ((opt = getopt(argc, argv, optstrings)) != -1) {
		switch (opt) {
		case 'a':
			g_ctrl.max_ar = atof(optarg);
			g_ctrl.min_ar = atof(argv[optind]);
			g_ctrl.cc_ratio = atof(argv[optind + 1]);
			break;
		case 'S':
			g_attr.sample.x = atoi(optarg);
			g_attr.sample.y = atoi(argv[optind]);
			g_attr.sample.w = atoi(argv[optind + 1]);
			g_attr.sample.h = atoi(argv[optind + 2]);
			g_attr.sample.scale_x = atoi(argv[optind + 3]);
			g_attr.sample.scale_y = atoi(argv[optind + 4]);
			break;
//		case 's':
//			g_save_path = optarg;
//			mkdir(g_save_path, 0776);
//			break;
		case 'b':
			g_attr.bin_bits = atoi(optarg);
			g_attr.nr_bins = atoi(argv[optind]);
			break;
		case 'c':
			g_ctrl.nr_cc_thd = atoi(optarg);
			break;
		case 'e':
			g_ctrl.sensitivity = atoi(optarg);
			break;
		case 'k':
			g_attr.skip_frames = atoi(optarg);
			break;
		case 'T':
			g_ctrl.train_enable = 1;
			g_ctrl.train_frames = atoi(optarg);
			break;
		case 't':
			g_ctrl.back_thd = atoi(optarg);
			g_ctrl.learn_thd = atoi(argv[optind]);
			g_ctrl.forget_thd = atoi(argv[optind + 1]);
			break;
		case 'p':
			g_pprc = atoi(optarg);
			break;
		case 'h':
			printf("Usage: %s [options]\n", argv[0]);
			printf("     -S <x y w h sx sy> | set sample region\n");
			printf("     -b <bin_bits nr_bins> | set binsetting\n");
			printf("     -k <skip_frames> | set skip\n");
			printf("     -a <max_ar min_ar cc_ratio>\n");
			printf("     -e <sensitivity>\n");
			printf("     -c <nr_cc_thd>\n");
			printf("     -T <train_frames>\n");
			printf("     -t <back_thd learn_thd forget_thd>\n");
			printf("     -p <pprc_mask:0b1 en postprocess,ob10 "
						"en ccinfo 0b100 en ccfilter>\n");
//			printf("     -s <save_path>\n");
			printf("     -l <logmask>\n");
			return (0);
		default:
			printf("unknown args!\n");
			return (-1);
		}

	}

	printf("attr: sample %d %d %d %d %d %d, bin: %d %d\n",
			(int)g_attr.sample.x,
			(int)g_attr.sample.y,
			(int)g_attr.sample.w,
			(int)g_attr.sample.h,
			(int)g_attr.sample.scale_x,
			(int)g_attr.sample.scale_y,
			(int)g_attr.bin_bits,
			(int)g_attr.nr_bins);

	return 0;
}
#endif
void md2_set_ctrl(struct rts_md2_ctrl *pctrl)
{
	if (g_ctrl.train_enable) {
		pctrl->train_enable = g_ctrl.train_enable;
		pctrl->train_frames = g_ctrl.train_frames;
	}

	if (g_ctrl.sensitivity >= 0)
		pctrl->sensitivity = g_ctrl.sensitivity;
	if (g_ctrl.back_thd) {
		pctrl->back_thd = g_ctrl.back_thd;
	}
	if (pctrl->back_thd && g_ctrl.learn_thd != 0 && g_ctrl.forget_thd != 0) {
		pctrl->learn_thd = g_ctrl.learn_thd;
		pctrl->forget_thd = g_ctrl.forget_thd;
	}
	if (g_ctrl.max_ar) {
		pctrl->max_ar = g_ctrl.max_ar;
		pctrl->min_ar = g_ctrl.min_ar;
		pctrl->cc_ratio = g_ctrl.cc_ratio;
	}
	if (g_ctrl.nr_cc_thd)
		pctrl->nr_cc_thd = g_ctrl.nr_cc_thd;
}

struct rts_md2_attr* md2_get_attr(void)
{
	return &g_attr;
}

void __draw_rect(uint8_t *d, int w, int h,
		int l, int u, int r, int b, int isbitmap)
{
	int s1 = u * w;
	int s2 = b * w;

	if (isbitmap) {
		for (int i = s1 + l; i <= s1 + r; i++)
			d[i/8] |= (1 << (i%8));
		for (int i = s2 + l; i <= s2 + r; i++)
			d[i/8] |= (1 << (i%8));
		for (int i = s1 + l; i <= s2 + l; i += w)
			d[i/8] |= (1 << (i%8));
		for (int i = s1 + r; i <= s2 + r; i += w)
			d[i/8] |= (1 << (i%8));
	} else {
		for (int i = s1 + l; i <= s1 + r; i++)
			d[i] = 255;
		for (int i = s2 + l; i <= s2 + r; i++)
			d[i] = 255;
		for (int i = s1 + l; i <= s2 + l; i += w)
			d[i] = 255;
		for (int i = s1 + r; i <= s2 + r; i += w)
			d[i] = 255;
	}
}


int md2_init(struct rts_md2_attr* attr, struct rts_md2_ctrl* ctrl)
{
	int ret=0;

	if (attr)
		memcpy(&g_attr, attr, sizeof(struct rts_md2_attr));
	if (ctrl)
		memcpy(&g_ctrl, ctrl, sizeof(struct rts_md2_ctrl));

	printf("attr: sample %d %d %d %d %d %d, bin: %d %d\n",
			(int)g_attr.sample.x,
			(int)g_attr.sample.y,
			(int)g_attr.sample.w,
			(int)g_attr.sample.h,
			(int)g_attr.sample.scale_x,
			(int)g_attr.sample.scale_y,
			(int)g_attr.bin_bits,
			(int)g_attr.nr_bins);

	return ret;
}

#endif
