/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include "rt_task.h"
#include <stdlib.h>
#include <rts_isp_errno.h>
#include <isp_utils.h>

#define EPSILON 1e-4

int isp_closexec(int fd, int set)
{
	return RTS_ISP_OK;
}

int isp_nonblock(int fd, int set)
{
	return RTS_ISP_OK;
}

uint32_t isp_upper_power_of_2(uint32_t val)
{
	val--;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	val++;

	return val;
}

static int __isp_lock_file(int fd, int is_lock, int block)
{
	return RTS_ISP_OK;
}

int isp_lock_file(int fd, int block)
{
	return __isp_lock_file(fd, RTS_ISP_TRUE, block);
}

int isp_unlock_file(int fd, int block)
{
	return __isp_lock_file(fd, RTS_ISP_FALSE, block);
}

ssize_t isp_strlcpy(char *dest, const char *src, size_t size)
{
	size_t len;

	if (!dest || !src || !size)
		return -RTS_ISP_EINVAL;

	len = strlen(src);
	len = (len >= size) ? size - 1 : len;
	memcpy(dest, src, len);
	dest[len] = '\0';
	return len;
}

int isp_get_val_weight(uint32_t val)
{
	int bits = 0;

	while (val) {
		bits++;
		val &= val - 1;
	};
	return bits;
}

int linear_intp(int x, int x0, int y0, int x1, int y1)
{
	if (x0 == x1)
		return (y0 + y1) / 2;
	return ((x - x0) * y1 + (x1 - x) * y0) / (x1 - x0);
}

float linear_intp_float(float x, float x0, float y0, float x1, float y1)
{
	if (x0 == x1)
		return (y0 + y1) / 2;
	return ((x - x0) * y1 + (x1 - x) * y0) / (x1 - x0);
}

int linear_intp_bound(int x, int x0, int y0, int x1, int y1)
{
	if (x0 < x1) {
		if (x < x0)
			return y0;
		else if (x > x1)
			return y1;
	} else {
		if (x < x1)
			return y1;
		else if (x > x0)
			return y0;
	}
	return linear_intp(x, x0, y0, x1, y1);
}

int calc_smooth(int current, int target, int div, int max)
{
	int step;

	if (!div || current == target)
		return current;
	step = clamp(abs((target - current) / div), 1, max);
	return current < target ? current + step : current - step;
}

float calc_smooth_float(float current, float target, float div, float max)
{
	float step;

	if (!div || fabsf(current - target) < EPSILON)
		return target;
	step = clamp(fabsf((target - current) / div), 1e-2, max);
	return current < target ? current + step : current - step;
}