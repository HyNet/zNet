
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_LIST_H_INCLUDED_
#define _ZNET_LIST_H_INCLUDED_

typedef struct znet_list_part_s  znet_list_part_t;

struct znet_list_part_s {
    void             *elts;
    znet_uint_t        nelts;
    znet_list_part_t  *next;
};

typedef struct {
    znet_list_part_t  *last;
    znet_list_part_t   part;
    size_t            size;
    znet_uint_t        nalloc;
    znet_pool_t       *pool;
} znet_list_t;

znet_list_t *znet_list_create(znet_pool_t *pool, znet_uint_t n, size_t size);

static inline znet_int_t
znet_list_init(znet_list_t *list, znet_pool_t *pool, znet_uint_t n, size_t size)
{
    list->part.elts = znet_palloc(pool, n * size);
    if (list->part.elts == NULL) {
        return -1;
    }

    list->part.nelts = 0;
    list->part.next = NULL;
    list->last = &list->part;
    list->size = size;
    list->nalloc = n;
    list->pool = pool;

    return 0;
}

void *znet_list_push(znet_list_t *list);
#endif /*_ZNET_LIST_H_INCLUDED_*/
