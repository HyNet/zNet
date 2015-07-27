
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
znet_socket_t znet_channel;
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
		znet_reap = 1;
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
znet_spawn_process(znet_spawn_proc_pt proc, char *name, znet_int_t respawn)
{
	printf("znet spawn worker process\n");
	znet_int_t s;
	znet_pid_t pid;

	if(respawn >= 0){
		s = respawn;
	}else{

		for(s = 0; s < znet_last_process; s++){
			if(znet_processes[s].pid == -1){
				break;
			}
		}
	
		if (s == ZNET_MAX_PROCESSES) {
            printf("no more than %d processes can be spawned", ZNET_MAX_PROCESSES);
            return -1;
        }
	}

	printf("spawn process: get empty slot: %d\n", (int)s);
	
	if (s == ZNET_MAX_PROCESSES){
		return ZNET_INVALID_PID;
	}

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, znet_processes[s].channel) == -1){
		return ZNET_INVALID_PID;
	}
	
	if (znet_nonblocking(znet_processes[s].channel[0]) == -1) {
        printf(" failed while spawning \"%s\"", name);
        znet_close_channel(znet_processes[s].channel);
        return ZNET_INVALID_PID;
    }
	
	if (znet_nonblocking(znet_processes[s].channel[1]) == -1) {
		printf(" failed while spawning \"%s\"", name);
		znet_close_channel(znet_processes[s].channel);
		return ZNET_INVALID_PID;
	}

	u_long on = 1;
	
	if (ioctl(znet_processes[s].channel[0], FIOASYNC, &on) == -1) {
		printf("ioctl(FIOASYNC) failed while spawning \"%s\"", name);
		znet_close_channel(znet_processes[s].channel);
		return ZNET_INVALID_PID;
	}
	
	if (fcntl(znet_processes[s].channel[0], F_SETOWN, znet_pid) == -1) {
		printf("fcntl(F_SETOWN) failed while spawning \"%s\"", name);
		znet_close_channel(znet_processes[s].channel);
		return ZNET_INVALID_PID;
	}
	
	if (fcntl(znet_processes[s].channel[0], F_SETFD, FD_CLOEXEC) == -1) {
		printf("fcntl(FD_CLOEXEC) failed while spawning \"%s\"", name);
		znet_close_channel(znet_processes[s].channel);
		return ZNET_INVALID_PID;
	}

	if (fcntl(znet_processes[s].channel[0], F_SETFD, FD_CLOEXEC) == -1) {
		printf("fcntl(FD_CLOEXEC) failed while spawning \"%s\"", name);
		znet_close_channel(znet_processes[s].channel);
		return ZNET_INVALID_PID;
	}
	
	znet_channel = znet_processes[s].channel[1];
	
	znet_process_slot = s;
		
	pid = fork();
	switch(pid){
	
	case 0:
		proc();
		break;
	default:
		break;
	}

	znet_processes[s].pid = pid;
	znet_processes[s].proc = proc;
	znet_processes[s].respawn = 1;

	if (s == znet_last_process) {
		znet_last_process++;
	}
	
	return pid;
}

static void 
znet_process_get_status(void)
{
	int status;
	znet_pid_t pid;
	int err;
	znet_int_t	i;

	printf("znet process get status.\n");
	for(;;){
		pid = waitpid(-1, &status, WNOHANG);
		printf("znet process waitpid %d\n", pid);
		
		if (0 == pid){
			printf("znet process wait success\n");
			return;
		}
		
		if (pid == -1) {
			err = errno;
			if (err == EINTR){
				printf("znet wait pid get EINTR\n");
				continue;
			}
			printf("znet wait pid failed\n");
			return;
		}

		
		for(i = 0; i < znet_last_process; i++) {
			if(znet_processes[i].pid == pid){
				znet_processes[i].status = status;
				znet_processes[i].exited = 1;
				break;	
			}
		}
		
		if (WTERMSIG(status)) {
			printf("process exited on singal %d\n", WTERMSIG(status));
		}else{
			printf("process exited code %d\n", WEXITSTATUS(status));
		}
		
		if (WEXITSTATUS(status) == 2){
			printf("exited with fatal code %d\n", WEXITSTATUS(status));
		}
		
	}	
	return;
}
