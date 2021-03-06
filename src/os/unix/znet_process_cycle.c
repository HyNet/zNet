
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

static void znet_worker_process_init(void);
static void znet_worker_process_cycle(void);
static void znet_worker_process_exit(void);
static void znet_start_worker_process(znet_int_t n);
static void znet_master_process_exit(void);
static void znet_pass_open_channel(znet_channel_t *ch);
static znet_uint_t znet_reap_children(void);
static void znet_channel_handler(znet_event_t *ev);

sig_atomic_t znet_terminate;
sig_atomic_t znet_reap;
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
			znet_master_process_exit();	
		}
		if (znet_reap){
			printf("reap worker process\n");
			znet_reap = 0;
			znet_reap_children();
			
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


static void 
znet_worker_process_init(void)
{
	sigset_t set;
	znet_int_t n;
	
	printf("worker process init\n");
	sigemptyset(&set);
	if (sigprocmask(SIG_SETMASK, &set, NULL) == -1) {
		printf("sigprocmask() failed\n");
    }

	if (znet_init_events() == -1){
		printf("init events failed\n");
	}
	for(n = 0; n < znet_last_process; n++) {
		if (znet_processes[n].pid == -1) {
            continue;
        }

        if (n == znet_process_slot) {
            continue;
        }

        if (znet_processes[n].channel[1] == -1) {
            continue;
        }
		
		printf("close worker process channel: %d slot\n", (int)n);
        if (close(znet_processes[n].channel[1]) == -1) {
			printf("close() channel failed\n");
        }
	}
	
	if (close(znet_processes[znet_process_slot].channel[0]) == -1) {
            printf("close() channel failed\n");
    }
	if(znet_add_channel_event(znet_channel, ZNET_READ_EVENT, znet_channel_handler) == -1)
	{
		exit(2);
	}
	
}


void znet_worker_process_cycle(void)
{
	znet_worker_process_init();
	znet_setproctitle("worker process");
	for(;;){
		printf("worker cycle...\n");
		if (znet_terminate){
			printf("stop worker cycle...\n");
			znet_worker_process_exit();
		}
		sleep(20);
		//znet_worker_process_exit();
	}
}


static void 
znet_worker_process_exit(void)
{
	printf("exit worker process\n");
	znet_done_events();		
	if(close(znet_processes[znet_process_slot].channel[1] == -1))
	{
		printf("worker process exit: close %d slot channel failed\n", (int)znet_process_slot);
	}
	exit(0);
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
		znet_spawn_process(znet_worker_process_cycle, "worker process", ZNET_PROCESS_RESPAWN);
		ch.pid = znet_processes[znet_process_slot].pid;
		ch.slot = znet_process_slot;
		ch.fd = znet_processes[znet_process_slot].channel[0];
		znet_pass_open_channel(&ch);
	}
}

static znet_uint_t 
znet_reap_children(void)
{
	znet_int_t		i, n;
	znet_channel_t ch;
	memset(&ch, 0, sizeof(znet_channel_t));
	
	ch.command = ZNET_CMD_CLOSE_CHANNEL;
	ch.fd = -1;
	
	for(i = 0; i < znet_last_process; i++){
		if(znet_processes[i].pid == -1)
			continue;
		if(znet_processes[i].exited){
			printf("reap children: %d slot\n",(int)i);
			znet_close_channel(znet_processes[i].channel);
			znet_processes[i].channel[0] = -1;
			znet_processes[i].channel[1] = -1;
			
			ch.pid = znet_processes[i].pid;
			ch.slot = i;
			
			for (n = 0; n < znet_last_process; n++) {
                if (znet_processes[n].exited
                        || znet_processes[n].pid == -1
                        || znet_processes[n].channel[0] == -1)
                {
                    continue;
                }

                znet_write_channel(znet_processes[n].channel[0],
                                      &ch, sizeof(znet_channel_t));
            }
			if(znet_spawn_process(znet_processes[i].proc,znet_processes[i].name, i) == -1)
			{
				continue;
			}
			ch.command = ZNET_CMD_OPEN_CHANNEL;
			ch.pid = znet_processes[znet_process_slot].pid;
			ch.slot = znet_process_slot;
			ch.fd = znet_processes[znet_process_slot].channel[0];
			znet_pass_open_channel(&ch);
		
		}
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
		znet_write_channel(znet_processes[i].channel[0], ch, sizeof(znet_channel_t));
	}
}

static void 
znet_channel_handler(znet_event_t *ev)
{
	znet_int_t n;
	znet_channel_t ch;
	znet_connection_t *c;
	
	c = ev->data;
	for(;;){
		n = znet_read_channel(c->fd, &ch, sizeof(znet_channel_t));
		if(n == -1){
			return;
		}

	}
	
}
