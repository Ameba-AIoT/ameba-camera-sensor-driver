#ifndef _ISP_LIST_H_INC_
#define _ISP_LIST_H_INC_

#include <stddef.h>

struct isp_list {
	struct isp_list *prev;
	struct isp_list *next;
};

#define LIST_INITIALIZER(q) { &(q), &(q) }

#define list_init(q) \
	do { \
		(q)->prev = q; \
		(q)->next = q; \
	} while (0)

#define isp_list_empty(h) (h == (h)->prev)

#define list_insert_head(h, n) \
	do { \
		(n)->next = (h)->next; \
		(n)->next->prev = n; \
		(n)->prev = h; \
		(h)->next = n; \
	} while (0)

#define list_insert_after(h, n)   list_insert_head(h, n)

#define list_insert_tail(h, n) \
	do { \
		(n)->prev = (h)->prev; \
		(n)->prev->next = n; \
		(n)->next = h; \
		(h)->prev = n; \
	} while (0)

#define list_insert_before(h, n)   list_insert_tail(h, n)

#define list_data(q, type, member) \
	((type *) ((size_t) q - offsetof(type, member)))

#define list_head(h) ((h)->next)

#define list_last(h) ((h)->prev)

#define list_next(q) ((q)->next)

#define list_prev(q) ((q)->prev)

#define list_remove(n) \
	do { \
		(n)->next->prev = (n)->prev; \
		(n)->prev->next = (n)->next; \
	} while (0)

#define list_remove_init(n) \
	do { \
		list_remove(n); \
		list_init(n); \
	} while (0)

#define list_split(h, q, n) \
	do { \
		(n)->prev = (h)->prev; \
		(n)->prev->next = n; \
		(n)->next = q; \
		(h)->prev = (q)->prev; \
		(h)->prev->next = h; \
		(q)->prev = n; \
	} while (0)

#define list_add_list(h, n) \
	do { \
		(h)->prev->next = (n)->next; \
		(n)->next->prev = (h)->prev; \
		(h)->prev = (n)->prev; \
		(h)->prev->next = h; \
	} while (0)

#define list_move_list(h, n) \
	do { \
		if (isp_list_empty(h)) { \
			list_init(n); \
		} else { \
			struct isp_list *q = list_head(h); \
			list_split(h, q, n); \
		} \
	} while (0)

#define list_foreach(q, h) \
	for ((q) = list_next(h); (q) != (h); (q) = list_next(q))

#define list_foreach_data(data, h, member) \
	for (data = list_data(list_next(h), typeof(*data), member); \
	     &data->member != (h); \
	     data = list_data(data->member.next, typeof(*data), member))

#define list_foreach_data_safe(data, n, h, member) \
	for (data = list_data(list_next(h), typeof(*data), member), \
	     n = list_data(data->member.next, typeof(*data), member); \
	     &data->member != (h); \
	     data = n, n = list_data(n->member.next, typeof(*n), member))

#endif /* _ISP_LIST_H_INC_ */
