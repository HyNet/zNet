
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>

typedef struct {
	int signo;
	char *signame;
	char *name;
	void (*handler)(int signo);
} znet_signal_t;

static void znet_signal_handler(int signo);
static void znet_process_get_status(void);

int znet_argc;
char **znet_os_argv;

znet_int_t znet_process_slot;
znet_int_t znet_last_process;
znet_process_t znet_processes[ZNET_MAX_PROCESSES];

znet_signal_t signals[]={
	{znet_signal_value(ZNET_TERMINATE_SIGNAL),
	"SIG"znet_value(ZNET_TERMINATE_SIGNAL),
	"stop",
	znet_signal_handler},

	{ SIGCHLD, "SIGCHLD", "", znet_signal_handler  },

	{ 0, NULL, "", NULL }
};

znet_int_t 
znet_init_signals(void)
{
	znet_signal_t *sig;
	struct sigaction sa;
	for(sig=signals; sig->signo != 0; sig++) {
		memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = sig->handler;
		sigemptyset(&sa.sa_mask);
		if (sigaction(sig->signo, &sa, NULL) == -1) {
			return -1;
		}
	}
	return 0;
}

void 
znet_signal_handler(int signo)
{
	printf("signal handler.\n");
	switch(signo){
	case znet_signal_value(ZNET_TERMINATE_SIGNAL):
		znet_terminate = 1;
		break;
	case SIGCHLD:
		znet_process_get_status();
		break;
	default:
		break;
	}	
}


znet_int_t 
znet_os_signal_process(char *sig, znet_int_t pid)
{
	znet_signal_t *psig;
	
	for(psig = signals; psig != 0; psig++) {
		if (strcmp(sig, signals->name) == 0) {
			if (kill(pid, psig->signo) != -1) 
				return 0;
		}
	}
	
	return 1;
}



znet_pid_t 
znet_spawn_process(znet_spawn_proc_pt proc, char *name)
{
	printf("znet spawn worker process\n");
	znet_pid_t pid;
	
	pid = fork();
	switch(pid){
	
	case 0:
		proc();
		break;
	default:
		break;
	}
	
	return pid;
}

static void 
znet_process_get_status(void)
{
	int status;
	znet_pid_t pid;
	int err;
	printf("znet process get status.\n");
	for(;;){
		pid = waitpid(-1, &status, WNOHANG);
		printf("znet process waitpid %d\n", pid);
		if (0 == pid){
			return;
		}
		if (pid == -1) {
			err = errno;
			if (err == EINTR){
				continue;
			}
			return;
		}
	}	
	return;
}
