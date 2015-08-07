
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

#endif /*_ZNET_ARRAY_H_INCLUDED_*/
