
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

znet_queue_t *
znet_queue_middle(znet_queue_t *queue)
{
	znet_queue_t  *middle, *next;

    middle = znet_queue_head(queue);

    if (middle == znet_queue_last(queue)) {
        return middle;
    }

    next = znet_queue_head(queue);

    for ( ;; ) {
        middle = znet_queue_next(middle);

        next = znet_queue_next(next);

        if (next == znet_queue_last(queue)) {
            return middle;
        }

        next = znet_queue_next(next);

        if (next == znet_queue_last(queue)) {
            return middle;
        }
    }
}


void znet_queue_sort(znet_queue_t *queue,
    znet_int_t (*cmp)(const znet_queue_t *, const znet_queue_t *))
{
	znet_queue_t  *q, *prev, *next;

    q = znet_queue_head(queue);

    if (q == znet_queue_last(queue)) {
        return;
    }

    for (q = znet_queue_next(q); q != znet_queue_sentinel(queue); q = next) {

        prev = znet_queue_prev(q);
        next = znet_queue_next(q);

        znet_queue_remove(q);

        do {
            if (cmp(prev, q) <= 0) {
                break;
            }

            prev = znet_queue_prev(prev);

        } while (prev != znet_queue_sentinel(queue));

        znet_queue_insert_after(prev, q);
    }	
}


