
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_CHANNEL_H_INCLUDED_
#define _ZNET_CHANNEL_H_INCLUDED_

#include<znet_core.h>

typedef struct {
	znet_uint_t command;
	znet_pid_t	pid;
	znet_int_t	slot;
	int			fd;
}znet_channel_t;

#endif /*_ZNET_CHANNEL_H_INCLUDED_*/
