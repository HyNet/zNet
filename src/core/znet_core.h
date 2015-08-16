
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_CORE_H_INCLUDED_
#define _ZNET_CORE_H_INCLUDED_

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<sys/wait.h>
#include<sys/ioctl.h>
#include<errno.h>
#include<unistd.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>



typedef intptr_t	znet_int_t;
typedef uintptr_t	znet_uint_t;
typedef intptr_t 	znet_flag_t;
typedef int			znet_fd_t;
typedef struct znet_event_s znet_event_t;
typedef struct znet_listening_s znet_listening_t;
typedef struct znet_connection_s znet_connection_t;
typedef struct znet_pool_s		znet_pool_t;
typedef void (*znet_event_handler_pt)(znet_event_t *ev);
typedef void (*znet_connection_handler_pt)(znet_connection_t *c);

#include<znet.h>
#include<znet_cycle.h>
#include<znet_palloc.h>
#include<znet_string.h>
#include<znet_array.h>
#include<znet_list.h>
#include<znet_queue.h>
#include<znet_setproctitle.h>
#include<znet_socket.h>
#include<znet_event.h>
#include<znet_connection.h>
#include<znet_process.h>
#include<znet_process_cycle.h>


#include<znet_channel.h>


#define znet_signal_helper(n)	SIG##n
#define znet_signal_value(n)	znet_signal_helper(n)

#define znet_value_helper(n)	#n
#define znet_value(n)	znet_value_helper(n)

#define ZNET_SHUTDOWN_SIGNAL      QUIT
#define ZNET_TERMINATE_SIGNAL     TERM
#define ZNET_NOACCEPT_SIGNAL      WINCH
#define ZNET_RECONFIGURE_SIGNAL   HUP

#define ZNET_REOPEN_SIGNAL        USR1
#define ZNET_CHANGEBIN_SIGNAL     USR2



#endif /*_ZNET_CORE_H_INCLUDED_*/
