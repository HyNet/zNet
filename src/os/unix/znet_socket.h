
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_SOCKET_H_INCLUDED_
#define _ZNET_SOCKET_H_INCLUDED_

typedef int znet_socket_t;

#define znet_socket		socket
#define znet_socket_n	"socket()"

#define znet_nonblocking(s)  fcntl(s, F_SETFL, fcntl(s, F_GETFL) | O_NONBLOCK)
#define znet_nonblocking_n   "fcntl(O_NONBLOCK)"

#define znet_blocking(s)     fcntl(s, F_SETFL, fcntl(s, F_GETFL) & ~O_NONBLOCK)
#define znet_blocking_n      "fcntl(!O_NONBLOCK)"


#define znet_shutdown_socket    shutdown
#define znet_shutdown_socket_n  "shutdown()"

#define znet_close_socket    close
#define znet_close_socket_n  "close() socket"


#endif /*_ZNET_SOCKET_H_INCLUDED_*/
