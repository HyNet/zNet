
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

void 
znet_array_destroy(znet_array_t *a)
{
	znet_pool_t  *p;

    p = a->pool;

    if ((u_char *) a->elts + a->size * a->nalloc == p->d.last) {
        p->d.last -= a->size * a->nalloc;
    }

    if ((u_char *) a + sizeof(znet_array_t) == p->d.last) {
        p->d.last = (u_char *) a;
    }
}

void *znet_array_push(znet_array_t *a)
{
	void        *elt, *new;
    size_t       size;
    znet_pool_t  *p;

    if (a->nelts == a->nalloc) {

        /* the array is full */

        size = a->size * a->nalloc;

        p = a->pool;

        if ((u_char *) a->elts + size == p->d.last
            && p->d.last + a->size <= p->d.end)
        {
            /*
             * the array allocation is the last in the pool
             * and there is space for new allocation
             */

            p->d.last += a->size;
            a->nalloc++;

        } else {
            /* allocate a new array */

            new = znet_palloc(p, 2 * size);
            if (new == NULL) {
                return NULL;
            }

            memcpy(new, a->elts, size);
            a->elts = new;
            a->nalloc *= 2;
        }
    }

    elt = (u_char *) a->elts + a->size * a->nelts;
    a->nelts++;

    return elt;
}

void *znet_array_push_n(znet_array_t *a, znet_uint_t n)
{
	void        *elt, *new;
    size_t       size;
    znet_uint_t   nalloc;
    znet_pool_t  *p;

    size = n * a->size;

    if (a->nelts + n > a->nalloc) {

        /* the array is full */

        p = a->pool;

        if ((u_char *) a->elts + a->size * a->nalloc == p->d.last
            && p->d.last + size <= p->d.end)
        {
            /*
             * the array allocation is the last in the pool
             * and there is space for new allocation
             */

            p->d.last += size;
            a->nalloc += n;

        } else {
            /* allocate a new array */

            nalloc = 2 * ((n >= a->nalloc) ? n : a->nalloc);

            new = znet_palloc(p, nalloc * a->size);
            if (new == NULL) {
                return NULL;
            }

            memcpy(new, a->elts, a->nelts * a->size);
            a->elts = new;
            a->nalloc = nalloc;
        }
    }

    elt = (u_char *) a->elts + a->size * a->nelts;
    a->nelts += n;

    return elt;
}
