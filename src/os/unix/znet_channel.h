
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


znet_int_t znet_write_channel(znet_socket_t s, znet_channel_t *ch, size_t size);
znet_int_t znet_read_channel (znet_socket_t s, znet_channel_t *ch, size_t size);
void znet_close_channel(int *fd);



#endif /*_ZNET_CHANNEL_H_INCLUDED_*/
