
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

#ifndef _ZNET_QUEUE_H_INCLUDED_
#define _ZNET_QUEUE_H_INCLUDED_

typedef struct znet_queue_s  znet_queue_t;

struct znet_queue_s {
    znet_queue_t  *prev;
    znet_queue_t  *next;
};

#define znet_queue_init(q)					\
	(q)->prev = q;							\
	(q)->next = q

#define znet_queue_empty(h)					\
	(h == (h)->prev)

#define znet_queue_insert_head(h, x)		\
	(x)->next = (h)->next;					\
	(x)->next->prev = x;					\
	(x)->prev = h;							\
	(h)->next = x

#define znet_queue_insert_after znet_queue_insert_head

#define znet_queue_insert_tail(h, x)		\
	(x)->prev = (h)->prev;					\
	(x)->prev->next = x;					\
	(x)->next = h;							\
	(h)->prev = x

#define znet_queue_head(h)					\
	(h)->next

#define znet_queue_last(h)					\
	(h)->prev

#define znet_queue_sentinel(h)				\
	(h)
#define znet_queue_next(h)					\
	(h)->next

#define znet_queue_prev(q)					\
	(q)->prev

#endif /*_ZNET_QUEUE_H_INCLUDED_*/
