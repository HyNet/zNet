
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


