#ifndef _ISP_PLUGIN_H_INC_
#define _ISP_PLUGIN_H_INC_

#include <rtsavisp.h>

struct isp_plugin {
	char *path;
	char *func;
	void *dl_handle;
	void *ops_handle;
};

int isp_plugin_load(struct isp_plugin *plugin,
		    const char *path, const char *func);
int isp_plugin_unload(struct isp_plugin *plugin);

#endif /* _ISP_PLUGIN_H_INC_ */
