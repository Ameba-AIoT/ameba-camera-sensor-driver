/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_top.h>
#include <isp_algo.h>
#include <isp_core.h>
#include <isp_notify.h>


#define ISP_DEBUG_TYPE ISP_DEBUG_ALGO

static inline int algo_id_to_type(enum rts_isp_algo_id id)
{
	return id / ISP_MAX_ALGO_NUM;
}

static inline int algo_id_to_index(enum rts_isp_algo_id id)
{
	return id % ISP_MAX_ALGO_NUM;
}

static struct isp_algo_attr **
algo_get_attr_array(struct isp_algo_manager *algom, enum rts_isp_algo_type type)
{
	if (!algom)
		return NULL;

	switch (type) {
	case RTS_ISP_ALGO_AE:
		return algom->ae;
	case RTS_ISP_ALGO_AWB:
		return algom->awb;
	case RTS_ISP_ALGO_AF:
		return algom->af;
	case RTS_ISP_ALGO_MD:
		return algom->md;
	case RTS_ISP_ALGO_OTHER:
		return algom->other;
	default:
		return NULL;
	}
}

static inline int algo_check_id(int id)
{
	if (id < 0 || id >= _RTS_ISP_ALGO_ID_NUM)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int algo_check(struct isp_algo_manager *algom,
		      const struct rts_isp_algo *algo)
{
	int i;
	struct isp_algo_attr **attr;

	if (!algom || !algo || !algo->path || algo_check_id(algo->id))
		return -RTS_ISP_EINVAL;

	attr = algo_get_attr_array(algom, (enum rts_isp_algo_type)algo_id_to_type(algo->id));
	if (!attr)
		return -RTS_ISP_EINVAL;

	if (attr[algo_id_to_index(algo->id)])
		return -RTS_ISP_ECONFLICT;

	for (i = 0; i < ISP_MAX_ALGO_NUM; i++) {
		if (!attr[i])
			continue;
		if (strcmp(attr[i]->plugin.path, algo->path) == 0)
			return -RTS_ISP_EEXIST;
	}

	return RTS_ISP_OK;
}

static int algo_find_algo_avalible(struct isp_algo_manager *algom,
				   enum rts_isp_algo_type type, int exclude)
{
	int i;
	struct isp_algo_attr **attr;

	attr = algo_get_attr_array(algom, type);
	//if (attr)
	//	return -RTS_ISP_EINVAL;
	if (!attr)
		return -1;

	for (i = 0; i < ISP_MAX_ALGO_NUM; i++)
		if (attr[i] && attr[i]->id != (unsigned int)exclude)
			return i;

	return -1;
}

static int algo_notify_change(uint32_t isp_id, enum rts_isp_algo_id id)
{
	uint32_t notify_data;

	if (isp_top_get_status() < RTS_ISP_RUNNING)
		return RTS_ISP_OK;

	notify_data = 1 << algo_id_to_type(id);
	return isp_core_notify(isp_top_get_core(isp_id),
			       ISP_NOTIFY_ALGO_UPDATE,
			       &notify_data, sizeof(notify_data));
}

static int algo_get_algo(struct isp_algo_manager *algom, uint32_t isp_id,
			 enum rts_isp_algo_type type, const void **algo)
{
	int index;
	struct isp_algo_attr **attr;

	if (!algom || isp_id >= _ISP_ID_NUM || !algo ||
	    type >= _RTS_ISP_ALGO_TYPE_NUM) {
		isp_error("%s %d %d \r\n", __FUNCTION__, isp_id, type);
		return -RTS_ISP_EINVAL;
	}


	index = algom->binding[isp_id].index[type];
	if (index < 0 || index >= ISP_MAX_ALGO_NUM) {
		isp_error("%s %d \r\n", __FUNCTION__, index);
		return -RTS_ISP_EINVAL;
	}

	attr = algo_get_attr_array(algom, type);
	if (!attr || !attr[index]){
		isp_error("%s 0x%08x 0x%08x \r\n", __FUNCTION__, (unsigned int)attr, (unsigned int)attr[index]);
		return -RTS_ISP_EINVAL;
	}
	*algo = attr[index]->plugin.ops_handle;

	return RTS_ISP_OK;
}

int isp_algo_init(struct isp_algo_manager *algom)
{
	int type;
	uint32_t isp_id;

	if (!algom)
		return -RTS_ISP_EINVAL;

	memset(algom, 0, sizeof(*algom));
	for (isp_id = 0; isp_id < _ISP_ID_NUM; isp_id++)
		for (type = 0; type < _RTS_ISP_ALGO_TYPE_NUM; type++)
			algom->binding[isp_id].index[type] = -1;

	return RTS_ISP_OK;
}

int isp_algo_cleanup(struct isp_algo_manager *algom)
{
	int isp_id;
	int type;
	int index;

	if (!algom)
		return -RTS_ISP_EINVAL;

	for (type = 0; type < _RTS_ISP_ALGO_TYPE_NUM; type++) {
		for (index = 0; index < ISP_MAX_ALGO_NUM; index++) {
			struct isp_algo_attr **attr;

			attr = algo_get_attr_array(algom, (enum rts_isp_algo_type)type);
			if (!attr || !attr[index])
				continue;
			for (isp_id = ISP0; isp_id < _ISP_ID_NUM; isp_id++)
				isp_algo_unbind(algom, isp_id, attr[index]->id);
			isp_algo_unregister(algom, attr[index]->id);
		}
	}

	debug("%s ok\n", __func__);

	return RTS_ISP_OK;
}

//Linux & FreeRTOS use same static ISP algo
int isp_algo_register(struct isp_algo_manager *algom,
		      const struct rts_isp_algo *algo)
{
	int ret;
	struct isp_algo_attr *new_attr;
	struct isp_algo_attr **attr;
	const char *func=NULL;

	if (!algom)
		return -RTS_ISP_EINVAL;
	ret = algo_check(algom, algo);
	if (ret)
		return ret;

	if (!isp_calloc_item(new_attr))
		return -RTS_ISP_ENOMEM;
	new_attr->id = algo->id;
	switch (algo_id_to_type(algo->id)) {
	case RTS_ISP_ALGO_AE:
		func = "rts_isp_get_ae_algo";
		new_attr->plugin.ops_handle = (void*)rts_isp_get_ae_algo();
		break;
	case RTS_ISP_ALGO_AWB:
		func = "rts_isp_get_awb_algo";
		new_attr->plugin.ops_handle = (void*)rts_isp_get_awb_algo();
		break;
	case RTS_ISP_ALGO_AF:
		func = "rts_isp_get_af_algo";
		new_attr->plugin.ops_handle = (void*)rts_isp_get_af_algo();
		break;
	case RTS_ISP_ALGO_MD:
		func = "rts_isp_get_md_algo";
		new_attr->plugin.ops_handle = (void*)rts_isp_get_md_algo();
		break;
	case RTS_ISP_ALGO_OTHER:
		func = "rts_isp_get_other_algo";
		new_attr->plugin.ops_handle = (void*)rts_isp_get_other_algo();
		break;
	default:
		func = NULL;
		new_attr->plugin.ops_handle = (void*)NULL;
		ret = -RTS_ISP_EINVAL;
		goto err;
	}
	ret = RTS_ISP_OK;

	attr = algo_get_attr_array(algom, (enum rts_isp_algo_type)algo_id_to_type(algo->id));
	if (attr == NULL)
		goto err;
	attr[algo_id_to_index(algo->id)] = new_attr;

	debug("register algo %s with id = %d ok\n",
	      func, algo->id);

	//return new_attr->id;
	return RTS_ISP_OK;
err:
	isp_perror(ret, "register algo %s %s with id = %d fail",
		   algo->path, func, algo->id);
	//isp_plugin_unload(&new_attr->plugin);
	isp_free(new_attr);
	return ret;
}

int isp_algo_unregister(struct isp_algo_manager *algom, enum rts_isp_algo_id id)
{
	int type;
	int index;
	uint32_t isp_id;
	struct isp_algo_attr **attr;

	if (!algom || algo_check_id(id))
		return -RTS_ISP_EINVAL;

	type = algo_id_to_type(id);
	index = algo_id_to_index(id);
	attr = algo_get_attr_array(algom, (enum rts_isp_algo_type)type);
	if (!attr)
		return -RTS_ISP_EINVAL;

	for (isp_id = 0; isp_id < _ISP_ID_NUM; isp_id++)
		if (algom->binding[isp_id].index[type] == index)
			return -RTS_ISP_EBUSY;

	if (!attr[index])
		return RTS_ISP_OK;

	//isp_plugin_unload(&attr[index]->plugin);
	isp_free(attr[index]);
	isp_info("unregister algo %d ok\r\n", id);

	return RTS_ISP_OK;
}

int isp_algo_get(struct isp_algo_manager *algom, struct rts_isp_algo *algo)
{
	int type;
	int index;
	struct isp_algo_attr **attr;

	if (!algom || !algo || algo_check_id(algo->id))
		return -RTS_ISP_EINVAL;

	type = algo_id_to_type(algo->id);
	index = algo_id_to_index(algo->id);
	attr = algo_get_attr_array(algom, (enum rts_isp_algo_type)type);
	if (!attr || !attr[index])
		return -RTS_ISP_EINVAL;

	algo->path = attr[index]->plugin.path;

	return RTS_ISP_OK;
}

int isp_algo_bind(struct isp_algo_manager *algom,
		  uint32_t isp_id, enum rts_isp_algo_id id)
{
	int ret;
	int type;
	int index;
	struct isp_algo_attr **attr;

	if (!algom || isp_id >= _ISP_ID_NUM || algo_check_id(id))
		return -RTS_ISP_EINVAL;

	type = algo_id_to_type(id);
	index = algo_id_to_index(id);
	attr = algo_get_attr_array(algom, (enum rts_isp_algo_type)type);
	if (!attr || !attr[index])
		return -RTS_ISP_EINVAL;

	algom->binding[isp_id].index[type] = index;
	ret = algo_notify_change(isp_id, id);
	if (ret) {
		isp_perror(ret, "notify algo change fail");
		return ret;
	}
	isp_info("%s %d to isp%d ok\r\n", __func__, id, isp_id);

	return RTS_ISP_OK;
}

int isp_algo_unbind(struct isp_algo_manager *algom,
		    uint32_t isp_id, enum rts_isp_algo_id id)
{
	int ret;
	int type;
	int index;
	if (!algom || isp_id >= _ISP_ID_NUM || algo_check_id(id)) {
		isp_error("%s 0x%08x %d %d", __func__, (unsigned int)algom, isp_id, algo_check_id(id));
		return -RTS_ISP_EINVAL;
	}

	type = algo_id_to_type(id);
	index = algo_id_to_index(id);

	if (algom->binding[isp_id].index[type] != index)
		return RTS_ISP_OK;

	algom->binding[isp_id].index[type] =
		algo_find_algo_avalible(algom, (enum rts_isp_algo_type)type, id);
	ret = algo_notify_change(isp_id, id);
	if (ret) {
		isp_error("%s notify algo change fail %d \r\n", __func__, ret);
		return ret;
	}
	isp_warning("%s %d to isp%d ok\r\n", __func__, id, isp_id);

	return RTS_ISP_OK;
}

int isp_algo_check_all_bound(struct isp_algo_manager *algom)
{
	int index;
	uint32_t isp_id;

	if (!algom)
		return -RTS_ISP_EINVAL;

	for (isp_id = 0; isp_id < _ISP_ID_NUM; isp_id++)
		for (index = 0; index < ISP_MAX_ALGO_NUM; index++)
			if (algom->binding[isp_id].index[index] == -1)
				return -RTS_ISP_ENOTREADY;
	return RTS_ISP_OK;
}

#define ALGO_GET_FUNC(type, upper) \
int isp_algo_get_##type(struct isp_algo_manager *algom, uint32_t isp_id, \
			const struct rts_isp_##type##_algo **type##_algo) \
{ \
	return algo_get_algo(algom, isp_id, RTS_ISP_ALGO_##upper, \
			     (const void **)type##_algo); \
} \

#define ALGO_GET_OTHER_FUNC(type) \
int isp_algo_get_##type(struct isp_algo_manager *algom, uint32_t isp_id, \
			const struct rts_isp_##type##_algo **type##_algo) \
{ \
	int ret; \
	const struct rts_isp_other_algo *other; \
	if (!type##_algo) \
		return -RTS_ISP_EINVAL; \
	ret = algo_get_algo(algom, isp_id, RTS_ISP_ALGO_OTHER, \
			    (const void **)&other); \
	if (ret) \
		return ret; \
	*type##_algo = &other->type; \
	return RTS_ISP_OK; \
}

ALGO_GET_FUNC(ae, AE);
ALGO_GET_FUNC(awb, AWB);
ALGO_GET_FUNC(af, AF);
ALGO_GET_FUNC(md, MD);
ALGO_GET_OTHER_FUNC(flick);
ALGO_GET_OTHER_FUNC(wdr);
