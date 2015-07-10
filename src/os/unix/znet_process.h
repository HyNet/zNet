
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_PROCESS_H_INCLUDED_
#define _ZNET_PROCESS_H_INCLUDED_

znet_int_t znet_init_signals(void);
znet_int_t znet_os_signal_process(char *sig, znet_int_t pid);

typedef pid_t znet_pid_t;

extern int znet_argc;
extern char **znet_os_argv;

#endif /*_ZNET_PROCESS_H_INCLUDED_*/

