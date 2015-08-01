
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_PALLOC_H_INCLUDED_
#define _ZNET_PALLOC_H_INCLUDED_

#include<znet_core.h>

typedef struct{
	u_char	*last;
	u_char	*end;
	znet_pool_t *next;
	znet_uint_t failed;
}znet_pool_data_t;

struct znet_pool_s{
};

#endif /*_ZNET_PALLOC_H_INCLUDED_*/
