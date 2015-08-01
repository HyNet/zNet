
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

znet_pool_t *
znet_create_pool(size_t size)
{
	znet_pool_t *p = (znet_pool_t *)malloc(size);
	if(p == NULL){
		return NULL;
	}
	p->d.last = (u_char *)p + sizeof(znet_pool_t);
	p->d.end  = (u_char *)p + size;
	p->d.next = NULL;
	p->d.failed = 0;

	size = size - sizeof(znet_pool_t);
	p->max = (size < ZNET_MAX_ALLOC_FROM_POOL)? size : ZNET_MAX_ALLOC_FROM_POOL;
	p->current = p;
	p->pool_cleanup_t = NULL;
	return p;
}

void 
znet_destroy_pool(znet_pool_t *pool)
{
	znet_pool_t *p,*n;
	znet_pool_cleanup_t *c;
	for(c = pool->cleanup; c; c = c->next){
		if(c->handler){
			c->handler(c->data);
		}
	}
	
	for(p = pool, n = pool->next; ;p = n; n = n->d.next){
		free(p);
		if(n == NULL){
			break;
		}
	}
	
}
