
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_CONNECTION_H_INCLUDED_
#define _ZNET_CONNECTION_H_INCLUDED_

#include<znet_core.h>

typedef struct {
	void	*data;
	znet_event_t *read;
	znet_event_t *write;
	znet_socket_t fd;
}znet_connection_t;


#endif /*_ZNET_CONNECTION_H_INCLUDED_*/
