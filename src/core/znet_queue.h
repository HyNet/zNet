
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

#define znet_queue_remove(x)				\
	(x)->prev->next = (x)->next;				\
	(x)->next->prev = (x)->prev

#define znet_queue_split(h, q, n)			\
	(n)->prev = (h)->prev;					\
	(n)->prev->next = n;					\
	(n)->next = q;							\
	(h)->prev = (q)->prev;					\
	(h)->prev->next = h;					\
	(q)->prev = n							

#define znet_queue_add(h,n)					\
	(h)->prev->next = (n)->next;			\
	(n)->next->prev = (h)->prev;			\
	(h)->prev = (n)->prev;					\
	(h)->prev->next = h

#define znet_queue_data(q, type, link)				\
	(type *)((u_char *) q - offsetof(type, link))

znet_queue_t *znet_queue_middle(znet_queue_t *queue);

void znet_queue_sort(znet_queue_t *queue,
    znet_int_t (*cmp)(const znet_queue_t *, const znet_queue_t *));

#endif /*_ZNET_QUEUE_H_INCLUDED_*/
