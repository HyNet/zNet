
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

znet_list_t *
znet_list_create(znet_pool_t *pool, znet_uint_t n, size_t size)
{
	znet_list_t  *list;

    list = znet_palloc(pool, sizeof(znet_list_t));
    if (list == NULL) {
        return NULL;
    }

    if (znet_list_init(list, pool, n, size) != 0) {
        return NULL;
    }

    return list;
}

void *znet_list_push(znet_list_t *l)
{
    void             *elt;
    znet_list_part_t  *last;

    last = l->last;

    if (last->nelts == l->nalloc) {

        /* the last part is full, allocate a new list part */

        last = znet_palloc(l->pool, sizeof(znet_list_part_t));
        if (last == NULL) {
            return NULL;
        }

        last->elts = znet_palloc(l->pool, l->nalloc * l->size);
        if (last->elts == NULL) {
            return NULL;
        }

        last->nelts = 0;
        last->next = NULL;

        l->last->next = last;
        l->last = last;
    }

    elt = (char *) last->elts + l->size * last->nelts;
    last->nelts++;

    return elt;
	
}
