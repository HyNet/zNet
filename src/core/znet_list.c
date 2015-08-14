
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
