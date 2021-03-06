
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_CONNECTION_H_INCLUDED_
#define _ZNET_CONNECTION_H_INCLUDED_

#include<znet_core.h>

struct znet_listening_s{
	znet_socket_t	fd;
	struct sockaddr *sockaddr;
	socklen_t		socklen;
	size_t			addr_text_len;
	char*			addr_text;
	int				type;
	int				backlog;
	int				rcvbuf;
	int				sndbuf;
	znet_connection_handler_pt handler;	
};

struct znet_connection_s{
	void	*data;
	znet_event_t *read;
	znet_event_t *write;
	znet_socket_t fd;
};

znet_listening_t *znet_create_listening(void* sockaddr, socklen_t socklen);


#endif /*_ZNET_CONNECTION_H_INCLUDED_*/
