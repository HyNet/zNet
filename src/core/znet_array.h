
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_ARRAY_H_INCLUDED_
#define _ZNET_ARRAY_H_INCLUDED_

#include<znet_core.h>

typedef struct{
	void *elts;
	znet_uint_t nelts;
	size_t size;
	znet_uint_t nalloc;
	znet_pool_t *pool;
}znet_array_t;

znet_array_t *znet_array_create(znet_pool_t *p, znet_uint_t n, size_t size);
void znet_array_destroy(znet_array_t *a);

static inline znet_int_t
znet_array_init(znet_array_t *array, znet_pool_t *pool, znet_uint_t n, size_t size)
{
	array->nelts = 0;
	array->size = size;
	array->nalloc = n;
	array->pool = pool;
	
	array->elts = znet_palloc(pool, n*size);
	if(array->elts == NULL){
		return -1;
	}
	return 0;
}

#endif /*_ZNET_ARRAY_H_INCLUDED_*/
