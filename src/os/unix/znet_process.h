
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_PROCESS_H_INCLUDED_
#define _ZNET_PROCESS_H_INCLUDED_

#define ZNET_MAX_PROCESSES 1024
#define ZNET_INVALID_PID -1


typedef pid_t znet_pid_t;

typedef void(*znet_spawn_proc_pt)(void);

typedef struct {
	znet_pid_t	pid;
	int			status;
	int			channel[2];
	znet_spawn_proc_pt proc;
} znet_process_t;


znet_int_t znet_init_signals(void);
znet_int_t znet_os_signal_process(char *sig, znet_int_t pid);
znet_pid_t znet_spawn_process(znet_spawn_proc_pt proc, char *name);


extern int znet_argc;
extern char **znet_os_argv;

#endif /*_ZNET_PROCESS_H_INCLUDED_*/

