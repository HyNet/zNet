
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

static void znet_worker_process_cycle(void);
static void znet_start_worker_process(znet_int_t n);
static void znet_master_process_exit(void);
static void znet_pass_open_channel(znet_channel_t *ch);
static znet_uint_t znet_reap_children(void);

sig_atomic_t znet_terminate;
znet_pid_t znet_pid;

static char master_process[] = "master process";

void znet_master_process_cycle(void)
{
	//char *title;
	sigset_t    set;
	struct itimerval itv;

	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigaddset(&set, SIGALRM);
	sigaddset(&set, SIGIO);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGHUP);
	sigaddset(&set, znet_signal_value(ZNET_RECONFIGURE_SIGNAL));
	sigaddset(&set, znet_signal_value(ZNET_REOPEN_SIGNAL));
	sigaddset(&set, znet_signal_value(ZNET_NOACCEPT_SIGNAL));
	sigaddset(&set, znet_signal_value(ZNET_TERMINATE_SIGNAL));
	sigaddset(&set, znet_signal_value(ZNET_CHANGEBIN_SIGNAL));
	
	sigprocmask(SIG_BLOCK, &set, NULL);
	sigemptyset(&set);
	
	znet_setproctitle(master_process);

	znet_start_worker_process(1);

	unsigned int delay = 0;
	
	for(;;){
		itv.it_interval.tv_sec = 0;
		itv.it_interval.tv_usec = 0;
		itv.it_value.tv_sec = delay / 1000;
		itv.it_value.tv_usec = ( delay % 1000 ) * 1000;

		setitimer(ITIMER_REAL, &itv, NULL);
		printf("cycle....\n");
		sigsuspend(&set);
		if (znet_terminate){
			printf("stop cycle..\n");
			znet_reap_children();
			znet_master_process_exit();	
		}
		printf("cycle after signal...\n");
	}
}

static void 
znet_master_process_exit(void)
{
	znet_delete_pidfile();
	exit(0);
}

void znet_worker_process_cycle(void)
{
	znet_setproctitle("worker process");
	for(;;){
		printf("worker cycle...\n");
		if (znet_terminate){
			printf("stop worker cycle...\n");
			exit(0);
		}
		sleep(10);
		exit(0);
	}
}


void 
znet_start_worker_process(znet_int_t n)
{
	znet_int_t i;
	znet_channel_t ch;
	memset(&ch, 0, sizeof(znet_channel_t));
	ch.command = ZNET_CMD_OPEN_CHANNEL;	
	for (i = 0; i < n; i++) {
		//znet spawn process
		znet_spawn_process(znet_worker_process_cycle, "worker process");
		ch.pid = znet_processes[znet_process_slot].pid;
		ch.slot = znet_process_slot;
		ch.fd = znet_processes[znet_process_slot].channel[0];
		znet_pass_open_channel(&ch);
	}
}

static znet_uint_t 
znet_reap_children(void)
{
	znet_int_t		i;
	znet_channel_t ch;
	memset(&ch, 0, sizeof(znet_channel_t));
	
	ch.command = ZNET_CMD_CLOSE_CHANNEL;
	ch.fd = -1;
	
	for(i = 0; i < znet_last_process; i++){
		if(znet_processes[i].pid == -1)
			continue;
	}
	return 0;
}

static void 
znet_pass_open_channel(znet_channel_t *ch)
{
	znet_int_t i;
	for (i = 0; i < znet_last_process; i++){
		if (i == znet_process_slot
			|| znet_processes[i].pid == -1
			|| znet_processes[i].channel[0] == -1)
		{
			continue;
		}
		// znet_write_channel
	}
}
