
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
#include<unistd.h>
#include<stdint.h>
#include<stdlib.h>

#include<znet_process.h>
#include<znet_process_cycle.h>


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


typedef intptr_t	znet_int_t;
typedef uintptr_t	znet_uint_t;
typedef intptr_t 	znet_flag_t;

#endif /*_ZNET_CORE_H_INCLUDED_*/
