
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_PROCESS_CYCLE_H_INCLUDED_
#define _ZNET_PROCESS_CYCLE_H_INCLUDED_

#include<znet_core.h>

void znet_master_process_cycle(void);


extern sig_atomic_t znet_terminate;
extern znet_pid_t znet_pid;

#endif /*_ZNET_PROCESS_CYCLE_H_INCLUDED_*/
