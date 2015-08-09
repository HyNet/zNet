
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

znet_array_t *
znet_array_create(znet_pool_t *p, znet_uint_t n, size_t size)
{
    znet_array_t *a;

    a = znet_palloc(p, sizeof(znet_array_t));
    if (a == NULL) {
        return NULL;
    }

    if (znet_array_init(a, p, n, size) != 0) {
        return NULL;
    }

    return a;
}

