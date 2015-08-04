
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_PALLOC_H_INCLUDED_
#define _ZNET_PALLOC_H_INCLUDED_

#include<znet_core.h>

#define ZNET_MAX_ALLOC_FROM_POOL 4095

typedef void(*znet_pool_cleanup_pt)(void *data);

typedef struct znet_pool_cleanup_s znet_pool_cleanup_t;

struct znet_pool_cleanup_s{
	znet_pool_cleanup_pt	handler;
	void					*data;
	znet_pool_cleanup_pt	*next;
};

typedef struct{
	u_char	*last;
	u_char	*end;
	znet_pool_t *next;
	znet_uint_t failed;
}znet_pool_data_t;

struct znet_pool_s{
	znet_pool_data_t	d;
	znet_pool_t			*current;
	znet_uint_t			max;
	znet_pool_cleanup_t	*cleanup;
};

znet_pool_t *znet_create_pool(size_t size);
void znet_destroy_pool(znet_pool_t *pool);

void *znet_pcalloc(znet_pool_t *pool, size_t size);


#endif /*_ZNET_PALLOC_H_INCLUDED_*/
