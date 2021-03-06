
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

static void *
znet_palloc_block(znet_pool_t *pool, size_t size);

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
	p->cleanup = NULL;
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
	
	for(p = pool, n = pool->d.next; ;p = n, n = n->d.next){
		free(p);
		if(n == NULL){
			break;
		}
	}
	
}

static void*
znet_palloc_block(znet_pool_t *pool, size_t size)
{
	u_char	*m;
	size_t psize;
	znet_pool_t *new, *p;
	
	psize = (size_t)(pool->d.end - (u_char*)pool);
	m = malloc(psize);
	if(m == NULL){
		return NULL;
	}
	
	new = (znet_pool_t*)m;
	new->d.end = m + psize;
	new->d.next = NULL;
	new->d.failed = 0;
	
	m += sizeof(znet_pool_data_t);
	new->d.last = m + size;
	
	for(p = pool->current; p->d.next; p = p->d.next){
		if(p->d.failed++ > 4){
			pool->current = p->d.next;
		}
	}
	p->d.next = new;
	return m;
}

void *
znet_pcalloc(znet_pool_t *pool, size_t size)
{
	void *p;
	p = znet_palloc(pool, size);
	if(p){
		memset(p, 0		, size);
	}	
	return p;
}

void *
znet_palloc(znet_pool_t *pool, size_t size)
{
    u_char      *m;
    znet_pool_t  *p;

    if (size <= pool->max) {

        p = pool->current;

        do {
            m = znet_align_ptr(p->d.last, ZNET_ALIGNMENT);

            if ((size_t) (p->d.end - m) >= size) {
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;

        } while (p);

        return znet_palloc_block(pool, size);
    }
	return NULL;

}

void *
znet_pnalloc(znet_pool_t *pool, size_t size)
{
	u_char      *m;
    znet_pool_t  *p;

    if (size <= pool->max) {

        p = pool->current;

        do {
            m = p->d.last;

            if ((size_t) (p->d.end - m) >= size) {
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;

        } while (p);

        return znet_palloc_block(pool, size);
    }
	return NULL;
}

znet_pool_cleanup_t *
znet_pool_cleanup_add(znet_pool_t *p, size_t size)
{
	znet_pool_cleanup_t  *c;

    c = znet_palloc(p, sizeof(znet_pool_cleanup_t));
    if (c == NULL) {
        return NULL;
    }

    if (size) {
        c->data = znet_palloc(p, size);
        if (c->data == NULL) {
            return NULL;
        }

    } else {
        c->data = NULL;
    }

    c->handler = NULL;
    c->next = p->cleanup;

    p->cleanup = c;


    return c;
}
