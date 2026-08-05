#include "cmsis_os2.h"
#include <errno.h>
#include "rts_errno.h"
//#include <media/videobuf2-memops.h>
#include <media/videobuf2-core.h>
#include <media/videobuf2-v4l2.h>
#include <media/v4l2-dev.h>
#include <rtscamkit.h>
#include <isp_utils.h>
#include "rts-dma-contig.h"
#include "rts_camera.h"
#include "rtx_mutex.h"
#include "rt_time.h"

extern void __enqueue_in_driver(struct vb2_buffer *vb);
extern int vb2_start_streaming(struct vb2_queue *q);


/**
 * __qbuf_mmap() - handle qbuf of an MMAP buffer
 */
static int __qbuf_mmap(struct vb2_buffer *vb, void *pb)
{
	int ret = 0;
#if 0
	if (pb)
		ret = call_bufop(vb->vb2_queue, fill_vb2_buffer,
				 vb, pb, vb->planes);
	return ret ? ret : call_vb_qop(vb, buf_prepare, vb);
#endif
	return ret;
}

static int __buf_prepare(struct vb2_buffer *vb, void *pb)
{
	struct vb2_queue *q = vb->vb2_queue;
	int ret;

	if (q->error) {
		rtsprintk(RTS_TRACE_ERROR, "fatal error occurred on queue\n");
		return -EIO;
	}

	vb->state = VB2_BUF_STATE_PREPARING;

	switch (q->memory) {
	case VB2_MEMORY_MMAP:
		ret = __qbuf_mmap(vb, pb);
		break;
//	case VB2_MEMORY_USERPTR:
//		ret = __qbuf_userptr(vb, pb);
//		break;
//	case VB2_MEMORY_DMABUF:
//		ret = __qbuf_dmabuf(vb, pb);
//		break;
	default:
		rtsprintk(RTS_TRACE_ERROR, "Invalid queue type\n");
		ret = -EINVAL;
	}

	if (ret)
		rtsprintk(RTS_TRACE_ERROR, "buffer preparation failed: %d\n", ret);
	vb->state = ret ? VB2_BUF_STATE_DEQUEUED : VB2_BUF_STATE_PREPARED;

	return ret;
}

/**
 * __verify_planes_array() - verify that the planes array passed in struct
 * v4l2_buffer from userspace can be safely used
 */
int __verify_planes_array(struct vb2_buffer *vb, struct v4l2_buffer *b)
{
	if (!V4L2_TYPE_IS_MULTIPLANAR(b->type))
		return 0;

	/* Is memory for copying plane information present? */
	if (b->m.planes == NULL) {
		rtsprintk(RTS_TRACE_ERROR, "multi-planar buffer passed but "
			   "planes array not provided\n");
		return -EINVAL;
	}

	if (b->length < vb->num_planes || b->length > VB2_MAX_PLANES) {
		rtsprintk(RTS_TRACE_ERROR, "incorrect planes array length, "
			   "expected %d, got %d\n", vb->num_planes, b->length);
		return -EINVAL;
	}

	return 0;
}


/**
 * __vb2_buf_mem_alloc() - allocate video memory for the given buffer
 */
static int __vb2_buf_mem_alloc(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;
	enum dma_data_direction dma_dir =
		q->is_output ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
	void *mem_priv;
	int plane;
	int ret = -ENOMEM;

	/*
	 * Allocate memory for all planes in this buffer
	 * NOTE: mmapped areas should be page aligned
	 */
	for (plane = 0; plane < (int)vb->num_planes; ++plane) {
		unsigned long size = PAGE_ALIGN(vb->planes[plane].length);

		mem_priv = call_ptr_memop(vb, alloc,
				q->dma_attrs, size, dma_dir);
		if (!mem_priv) {
			goto free;
		}

		/* Associate allocator private data with this plane */
		vb->planes[plane].mem_priv = mem_priv;
	}

	return 0;
free:
	/* Free already allocated memory if one of the allocations failed */
	for (; plane > 0; --plane) {
		call_void_memop(vb, put, vb->planes[plane - 1].mem_priv);
		vb->planes[plane - 1].mem_priv = NULL;
	}

	return ret;
}

/**
 * __vb2_buf_mem_free() - free memory of the given buffer
 */
static void __vb2_buf_mem_free(struct vb2_buffer *vb)
{
	unsigned int plane;

	for (plane = 0; plane < vb->num_planes; ++plane) {
		call_void_memop(vb, put, vb->planes[plane].mem_priv);
		vb->planes[plane].mem_priv = NULL;
		rtsprintk(RTS_TRACE_DEBUG, "freed plane %d of buffer %d\n", 
					plane, vb->index);
	}
}

/**
 * __setup_offsets() - setup unique offsets ("cookies") for every plane in
 * the buffer.
 */
static void __setup_offsets(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;
	unsigned int plane;
	unsigned long off = 0;

	if (vb->index) {
		struct vb2_buffer *prev = q->bufs[vb->index - 1];
		struct vb2_plane *p = &prev->planes[prev->num_planes - 1];

		off = PAGE_ALIGN(p->m.offset + p->length);
	}

	for (plane = 0; plane < vb->num_planes; ++plane) {
		vb->planes[plane].m.offset = off;

		rtsprintk(RTS_TRACE_DEBUG, "buffer %d, plane %d offset 0x%08lx\n",
				vb->index, plane, off);

		off += vb->planes[plane].length;
		off = PAGE_ALIGN(off);
	}
}

/**
 * __vb2_queue_alloc() - allocate videobuf buffer structures and (for MMAP type)
 * video buffer memory for all buffers/planes on the queue and initializes the
 * queue
 *
 * Returns the number of buffers successfully allocated.
 */
int __vb2_queue_alloc(struct vb2_queue *q, enum vb2_memory memory,
			     unsigned int num_buffers, unsigned int num_planes,
			     const unsigned plane_sizes[VB2_MAX_PLANES])
{
	unsigned int buffer, plane;
	struct vb2_buffer *vb;
	int ret;

	/* Ensure that q->num_buffers+num_buffers is below VB2_MAX_FRAME */
	num_buffers = min_t(unsigned int, num_buffers,
			    VB2_MAX_FRAME - q->num_buffers);

	for (buffer = 0; buffer < num_buffers; ++buffer) {
		/* Allocate videobuf buffer structures */
		vb = rts_calloc(1, q->buf_struct_size);
		if (!vb) {
			rtsprintk(RTS_TRACE_ERROR, "memory alloc for buffer struct failed\n");
			break;
		}

		vb->state = VB2_BUF_STATE_DEQUEUED;
		vb->vb2_queue = q;
		vb->num_planes = num_planes;
		vb->index = q->num_buffers + buffer;
		vb->type = q->type;
		vb->memory = memory;
		for (plane = 0; plane < num_planes; ++plane) {
			vb->planes[plane].length = plane_sizes[plane];
			vb->planes[plane].min_length = plane_sizes[plane];
		}
		q->bufs[vb->index] = vb;

		/* Allocate video buffer memory for the MMAP type */
		if (memory == VB2_MEMORY_MMAP) {
			ret = __vb2_buf_mem_alloc(vb);
			if (ret) {
				rtsprintk(RTS_TRACE_ERROR, "failed allocating memory for "
						"buffer %d\n", buffer);
				q->bufs[vb->index] = NULL;
				rts_free(vb);
				break;
			}
			__setup_offsets(vb);
			/*
			 * Call the driver-provided buffer initialization
			 * callback, if given. An error in initialization
			 * results in queue setup failure.
			 */
			ret = call_vb_qop(vb, buf_init, vb);
			if (ret) {
				rtsprintk(RTS_TRACE_ERROR, "buffer %d %p initialization"
					" failed\n", buffer, vb);
				__vb2_buf_mem_free(vb);
				q->bufs[vb->index] = NULL;
				rts_free(vb);
				break;
			}
		}
	}

	rtsprintk(RTS_TRACE_DEBUG, "allocated %d buffers, %d plane(s) each\n",
			buffer, num_planes);

	return buffer;
}

/**
 * __vb2_free_mem() - release all video buffer memory for a given queue
 */
static void __vb2_free_mem(struct vb2_queue *q, unsigned int buffers)
{
#if 0
	unsigned int buffer;
	struct vb2_buffer *vb;

	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		vb = q->bufs[buffer];
		if (!vb)
			continue;

		/* Free MMAP buffers or release USERPTR buffers */
//		if (q->memory == VB2_MEMORY_MMAP)
			__vb2_buf_mem_free(vb);
//		else if (q->memory == VB2_MEMORY_DMABUF)
//			__vb2_buf_dmabuf_put(vb);
//		else
//			__vb2_buf_userptr_put(vb);
	}
#endif
}

/**
 * __vb2_queue_free() - free buffers at the end of the queue - video memory and
 * related information, if no buffers are left return the queue to an
 * uninitialized state. Might be called even if the queue has already been freed.
 */
int __vb2_queue_free(struct vb2_queue *q, unsigned int buffers)
{
	unsigned int buffer;

	/*
	 * Sanity check: when preparing a buffer the queue lock is released for
	 * a short while (see __buf_prepare for the details), which would allow
	 * a race with a reqbufs which can call this function. Removing the
	 * buffers from underneath __buf_prepare is obviously a bad idea, so we
	 * check if any of the buffers is in the state PREPARING, and if so we
	 * just return -EAGAIN.
	 */
	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		if (q->bufs[buffer] == NULL)
			continue;
		if (q->bufs[buffer]->state == VB2_BUF_STATE_PREPARING) {
			rtsprintk(RTS_TRACE_ERROR, "preparing buffers, cannot free\n");
			return -EAGAIN;
		}
	}

	/* Call driver-provided cleanup function for each buffer, if provided */
	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		struct vb2_buffer *vb = q->bufs[buffer];

		if (vb && vb->planes[0].mem_priv)
			call_void_vb_qop(vb, buf_cleanup, vb);
	}

	/* Release video buffer memory */
	__vb2_free_mem(q, buffers);

	/* Free videobuf buffers */
	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		rts_free(q->bufs[buffer]);
		q->bufs[buffer] = NULL;
	}

	q->num_buffers -= buffers;
	if (!q->num_buffers) {
		q->memory = 0;
		INIT_LIST_HEAD(&q->queued_list);
	}
	return 0;
}

bool vb2_buffer_in_use(struct vb2_queue *q, struct vb2_buffer *vb)
{
	unsigned int plane;
	for (plane = 0; plane < vb->num_planes; ++plane) {
		void *mem_priv = vb->planes[plane].mem_priv;
		/*
		 * If num_users() has not been provided, call_memop
		 * will return 0, apparently nobody cares about this
		 * case anyway. If num_users() returns more than 1,
		 * we are not the only user of the plane's memory.
		 */
		if (mem_priv && call_memop(vb, num_users, mem_priv) > 1)
			return TRUE;
	}
	return FALSE;
}

/**
 * __vb2_dqbuf() - bring back the buffer to the DEQUEUED state
 */
static void __vb2_dqbuf(struct vb2_buffer *vb)
{
//	struct vb2_queue *q = vb->vb2_queue;
//	unsigned int i;

	/* nothing to do if the buffer is already dequeued */
	if (vb->state == VB2_BUF_STATE_DEQUEUED)
		return;

	vb->state = VB2_BUF_STATE_DEQUEUED;

	/* unmap DMABUF buffer */
//	if (q->memory == VB2_MEMORY_DMABUF)
//		for (i = 0; i < vb->num_planes; ++i) {
//			if (!vb->planes[i].dbuf_mapped)
//				continue;
//			call_void_memop(vb, unmap_dmabuf, vb->planes[i].mem_priv);
//			vb->planes[i].dbuf_mapped = 0;
//		}
}

/**
 * __vb2_get_done_vb() - get a buffer ready for dequeuing
 *
 * Will sleep if required for nonblocking == false.
 */
static int __vb2_get_done_vb(struct vb2_queue *q, struct vb2_buffer **vb,
			     void *pb, int nonblocking)
{
//	unsigned long flags;
	int ret = 0;

	/*
	 * Driver's lock has been held since we last verified that done_list
	 * is not empty, so no need for another list_empty(done_list) check.
	 */
	if (xQueueReceive(q->done_list, vb, portMAX_DELAY) == pdFALSE) {
		rtsprintk(RTS_TRACE_ERROR, "urb queue recv failed\n");
	} else {
		/*
		 * Only remove the buffer from done_list if all planes can be
		 * handled. Some cases such as V4L2 file I/O and DVB have pb
		 * == NULL; skip the check then as there's nothing to verify.
		 */
		if (pb) {
			ret = xSemaphoreTake(q->done_lock, ISP_SEM_TIMEOUT);
			if (ret != pdTRUE) {
				isp_error("__vb2_get_done_vb wait q->done_lock timeout\n\r");
				return -ETIMEDOUT;
			}
			ret = call_bufop(q, verify_planes_array, *vb, pb);
//			if (!ret)
//				list_del(&(*vb)->done_entry);
			//osMutexRelease(q->done_lock);
			xSemaphoreGive(q->done_lock);
		}
	}

	return ret;
}

void vb2_core_querybuf(struct vb2_queue *q, unsigned int index, void *pb)
{
	call_void_bufop(q, fill_user_buffer, q->bufs[index], pb);
}

int vb2_core_dqbuf(struct vb2_queue *q, unsigned int *pindex, void *pb,
		   bool nonblocking)
{
	struct vb2_buffer *vb = NULL;
	int ret;

	ret = __vb2_get_done_vb(q, &vb, pb, nonblocking);
	if (ret < 0)
		return ret;

	switch (vb->state) {
	case VB2_BUF_STATE_DONE:
		break;
	case VB2_BUF_STATE_ERROR:
		break;
	default:
		rtsprintk(RTS_TRACE_ERROR, "invalid buffer state\n");
		return -EINVAL;
	}

	call_void_vb_qop(vb, buf_finish, vb);

	if (pindex)
		*pindex = vb->index;

	/* Fill buffer information for the userspace */
	if (pb)
		call_void_bufop(q, fill_user_buffer, vb, pb);

	/* Remove from videobuf queue */
	list_del(&vb->queued_entry);
	q->queued_count--;

//	trace_vb2_dqbuf(q, vb);

	/* go back to dequeued state */
	__vb2_dqbuf(vb);

	rtsprintk(RTS_TRACE_DEBUG, "dqbuf of buffer %d, with state %d\n",
				vb->index, vb->state);

	return 0;

}

int vb2_core_qbuf(struct vb2_queue *q, unsigned int index, void *pb)
{
	struct vb2_buffer *vb;
	int ret;

	if (q->error) {
		rtsprintk(RTS_TRACE_ERROR, "fatal error occurred on queue\n");
		return -EIO;
	}

	vb = q->bufs[index];

	switch (vb->state) {
	case VB2_BUF_STATE_DEQUEUED:
		ret = __buf_prepare(vb, pb);
		if (ret)
			return ret;
		break;
	case VB2_BUF_STATE_PREPARED:
		break;
	case VB2_BUF_STATE_PREPARING:
		rtsprintk(RTS_TRACE_ERROR, "buffer still being prepared\n");
		return -EINVAL;
	default:
		rtsprintk(RTS_TRACE_ERROR, "invalid buffer state %d\n", vb->state);
		return -EINVAL;
	}

	/*
	 * Add to the queued buffers list, a buffer will stay on it until
	 * dequeued in dqbuf.
	 */
	list_add_tail(&vb->queued_entry, &q->queued_list);

	q->queued_count++;
	q->waiting_for_buffers = FALSE;
	vb->state = VB2_BUF_STATE_QUEUED;

	if (pb)
		call_void_bufop(q, copy_timestamp, vb, pb);

//	trace_vb2_qbuf(q, vb);

	/*
	 * If already streaming, give the buffer to driver for processing.
	 * If not, the buffer will be given to driver on next streamon.
	 */
	if (q->start_streaming_called)
		__enqueue_in_driver(vb);

	/* Fill buffer information for the userspace */
	if (pb)
		call_void_bufop(q, fill_user_buffer, vb, pb);

	/*
	 * If streamon has been called, and we haven't yet called
	 * start_streaming() since not enough buffers were queued, and
	 * we now have reached the minimum number of queued buffers,
	 * then we can finally call start_streaming().
	 */
	if (q->streaming && !q->start_streaming_called &&
	    q->queued_count >= q->min_buffers_needed) {
		ret = vb2_start_streaming(q);
		if (ret)
			return ret;
	}

	rtsprintk(RTS_TRACE_DEBUG, "qbuf of buffer %d succeeded\n", vb->index);
	return 0;
}

/**
 * __vb2_queue_cancel() - cancel and stop (pause) streaming
 *
 * Removes all queued buffers from driver's queue and all buffers queued by
 * userspace from videobuf's queue. Returns to state after reqbufs.
 */
void __vb2_queue_cancel(struct vb2_queue *q)
{
	unsigned int i;

	/*
	 * Tell driver to stop all transactions and release all queued
	 * buffers.
	 */
	if (q->start_streaming_called)
		call_void_qop(q, stop_streaming, q);

	/*
	 * If you see this warning, then the driver isn't cleaning up properly
	 * in stop_streaming(). See the stop_streaming() documentation in
	 * videobuf2-core.h for more information how buffers should be returned
	 * to vb2 in stop_streaming().
	 */
	if (atomic_read_isp(&q->owned_by_drv_count)) {
		for (i = 0; i < q->num_buffers; ++i)
			if (q->bufs[i]->state == VB2_BUF_STATE_ACTIVE)
				vb2_buffer_done(q->bufs[i], VB2_BUF_STATE_ERROR);
		/* Must be zero now */
//		WARN_ON(atomic_read(&q->owned_by_drv_count));
	}

	q->streaming = 0;
	q->start_streaming_called = 0;
	q->queued_count = 0;
	q->error = 0;

	/*
	 * Remove all buffers from videobuf's list...
	 */
	INIT_LIST_HEAD(&q->queued_list);
	/*
	 * ...and done list; userspace will not receive any buffers it
	 * has not already dequeued before initiating cancel.
	 */
	//INIT_LIST_HEAD(&q->done_list);
	xQueueReset(q->done_list);
	atomic_set_isp(&q->owned_by_drv_count, 0);
	//wake_up_all(&q->done_wq);

	/*
	 * Reinitialize all buffers for next use.
	 * Make sure to call buf_finish for any queued buffers. Normally
	 * that's done in dqbuf, but that's not going to happen when we
	 * cancel the whole queue. Note: this code belongs here, not in
	 * __vb2_dqbuf() since in vb2_core_dqbuf() there is a critical
	 * call to __fill_user_buffer() after buf_finish(). That order can't
	 * be changed, so we can't move the buf_finish() to __vb2_dqbuf().
	 */
	for (i = 0; i < q->num_buffers; ++i) {
		struct vb2_buffer *vb = q->bufs[i];

		if (vb->state != VB2_BUF_STATE_DEQUEUED) {
			vb->state = VB2_BUF_STATE_PREPARED;
			call_void_vb_qop(vb, buf_finish, vb);
		}
		__vb2_dqbuf(vb);
	}
}

int vb2_core_queue_init(struct vb2_queue *q)
{
	int ret=0;
#if 0
	/*
	 * Sanity check
	 */
	if ((!q)			  ||
	    (!q->ops)		  ||
	    (!q->mem_ops)	  ||
	    (!q->type)		  ||
	    (!q->io_modes)	  ||
	    (!q->ops->queue_setup) ||
	    (!q->ops->buf_queue)) {
		ret = -EINVAL;
		goto err;
	}

	INIT_LIST_HEAD(&q->queued_list);

	//INIT_LIST_HEAD(&q->done_list);
	if ((q->done_list = xQueueCreate(VB2_MAX_FRAME, sizeof(void *))) == NULL)
	{
		rtsprintk(RTS_TRACE_ERROR, "done_list create fail!\n");
		ret = -ENOMEM;
	    goto err;
	}

	q->done_lock = xSemaphoreCreateMutex();
	if (!q->done_lock) {
		rtsprintk(RTS_TRACE_ERROR, "vb2 queue done_lock allocate mutex fail\n");
		ret = -ENOMEM;
		goto err;
	}

	//mutex_init(&q->mmap_lock);
	q->mmap_lock = xSemaphoreCreateMutex();
	if (!q->mmap_lock) {
		rtsprintk(RTS_TRACE_ERROR, "vb2 queue mmap_lock allocate mutex fail\n");
		ret = -ENOMEM;
		goto err;
	}

//	init_waitqueue_head(&q->done_wq);

	if (q->buf_struct_size == 0)
		q->buf_struct_size = sizeof(struct vb2_buffer);

	return 0;

err:
	if (q->done_list) {
		vQueueDelete(q->done_list);
	}
	if (q->done_lock) {
//		osMutexDelete(q->done_lock);
		vSemaphoreDelete(q->done_lock);
		q->done_lock = NULL;
	}
	if (q->mmap_lock) {

		//osMutexDelete(q->mmap_lock);
		vSemaphoreDelete(q->mmap_lock);
		q->mmap_lock = NULL;
	}
#endif
	return ret;
}

void vb2_core_queue_release(struct vb2_queue *q)
{
#if 0
//	__vb2_cleanup_fileio(q);
	__vb2_queue_cancel(q);
	if (xSemaphoreTake(q->mmap_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("vb2_core_queue_release wait q->mmap_lock timeout\n\r");
		return;
	}
	__vb2_queue_free(q, q->num_buffers);
	//osMutexRelease(q->mmap_lock);
	xSemaphoreGive(q->mmap_lock);

#endif
}

/*
static int v4l_enable_media_source(struct video_device *vdev)
{
	struct media_device *mdev = vdev->entity.graph_obj.mdev;
	int ret;

	if (!mdev || !mdev->enable_source)
		return 0;
	ret = mdev->enable_source(&vdev->entity, &vdev->pipe);
	if (ret)
		return -EBUSY;
	return 0;
}

static int v4l_vb2q_enable_media_source(struct vb2_queue *q)
{
	struct video_device *vdev = q->owner;

	if (vdev)
		return v4l_enable_media_source(vdev);
	return 0;
}
*/

int vb2_core_streamon(struct vb2_queue *q, unsigned int type)
{
	int ret;

	if (type != q->type) {
		rtsprintk(RTS_TRACE_ERROR, "invalid stream type\n");
		return -EINVAL;
	}

	if (q->streaming) {
		rtsprintk(RTS_TRACE_WARNING, "already streaming\n");
		return 0;
	}

	if (!q->num_buffers) {
		rtsprintk(RTS_TRACE_ERROR, "no buffers have been allocated\n");
		return -EINVAL;
	}

	if (q->num_buffers < q->min_buffers_needed) {
		rtsprintk(RTS_TRACE_ERROR, "need at least %u allocated buffers\n",
				q->min_buffers_needed);
		return -EINVAL;
	}

	/*
	 * Tell driver to start streaming provided sufficient buffers
	 * are available.
	 */
	if (q->queued_count >= q->min_buffers_needed) {
		//q.owner is null 
		//ret = v4l_vb2q_enable_media_source(q);
		//if (ret)
		//	return ret;
		ret = vb2_start_streaming(q);
		if (ret) {
			__vb2_queue_cancel(q);
			return ret;
		}
	}

	q->streaming = 1;

	printf("%s successful\n", __func__);
	return 0;
}

int vb2_core_streamoff(struct vb2_queue *q, unsigned int type)
{
	if (type != q->type) {
		rtsprintk(RTS_TRACE_ERROR, "invalid stream type\n");
		return -EINVAL;
	}

	/*
	 * Cancel will pause streaming and remove all buffers from the driver
	 * and videobuf, effectively returning control over them to userspace.
	 *
	 * Note that we do this even if q->streaming == 0: if you prepare or
	 * queue buffers, and then call streamoff without ever having called
	 * streamon, you would still expect those buffers to be returned to
	 * their normal dequeued state.
	 */
	__vb2_queue_cancel(q);
	q->waiting_for_buffers = !q->is_output;
	q->last_buffer_dequeued = FALSE;

	printf("%s successful\n", __func__);
	return 0;
}
