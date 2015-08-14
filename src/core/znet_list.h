
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

#endif /*_ZNET_LIST_H_INCLUDED_*/
