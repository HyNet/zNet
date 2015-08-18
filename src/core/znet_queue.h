
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

#endif /*_ZNET_QUEUE_H_INCLUDED_*/
