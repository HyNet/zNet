
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_PROCESS_CYCLE_H_INCLUDED_
#define _ZNET_PROCESS_CYCLE_H_INCLUDED_

#include<znet_core.h>

#define ZNET_CMD_OPEN_CHANNEL 1
#define ZNET_CMD_CLOSE_CHANNEL 2
#define ZNET_CMD_QUIT			3
#define ZNET_CMD_TERMINATE		4
#define ZNET_CMD_REOPEN			5

void znet_master_process_cycle(void);


extern sig_atomic_t znet_terminate;
extern znet_pid_t znet_pid;

#endif /*_ZNET_PROCESS_CYCLE_H_INCLUDED_*/
