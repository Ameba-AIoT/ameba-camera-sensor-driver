/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

//#include <dlfcn.h>
#include <isp_utils.h>
#include <isp_log.h>
#include <isp_mem.h>
#include <isp_plugin.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_CORE

static int plugin_parse_ops_handle(struct isp_plugin *plugin)
{

#if 0
	void *(*func_ptr)(void);

	debug("get sym %s from plugin %s\n", plugin->func, plugin->path);
	func_ptr = dlsym(plugin->dl_handle, plugin->func);
	if (!func_ptr) {
		char *error = dlerror();

		isp_error("get func name %s fail: %s\n", plugin->func, error);
		return -RTS_ISP_EPLUGIN;
	}
	plugin->ops_handle = func_ptr();
	if (!plugin->ops_handle)
		return -RTS_ISP_EPLUGIN;
#endif
	return RTS_ISP_OK;
}

int isp_plugin_load(struct isp_plugin *plugin,
		    const char *path, const char *func)
{
	int ret;

#if 0
	if (!plugin || !path || !func)
		return -RTS_ISP_EINVAL;

	//if (access(path, R_OK | X_OK))
	//	return -errno;

	plugin->path = strdup(path);
	plugin->func = strdup(func);

	debug("get ops from %s\n", plugin->path);
	plugin->dl_handle = dlopen(plugin->path, RTLD_NOW);
	if (!plugin->dl_handle) {
		isp_error("open plugin %s fail: %s\n", plugin->path, dlerror());
		ret = -RTS_ISP_EPLUGIN;
		goto err;
	}
	ret = plugin_parse_ops_handle(plugin);
	if (ret)
		goto err;
#endif

	return RTS_ISP_OK;

//err:
//	isp_perror(ret, "load plugin fail");
//	isp_plugin_unload(plugin);
//	return ret;
}

int isp_plugin_unload(struct isp_plugin *plugin)
{
#if 0
	if (!plugin)
		return -RTS_ISP_EINVAL;

	isp_free(plugin->path);
	isp_free(plugin->func);
	isp_release(plugin->dl_handle, dlclose);
	plugin->ops_handle = NULL;
#endif
	return RTS_ISP_OK;
}
