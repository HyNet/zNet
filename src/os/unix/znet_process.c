
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

znet_signal_t signals[]={
	{znet_signal_value(ZNET_TERMINATE_SIGNAL),
	"SIG"znet_value(ZNET_TERMINATE_SIGNAL),
	"stop",
	znet_signal_handler},
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
	switch(signo){
	case znet_signal_value(ZNET_TERMINATE_SIGNAL):
		znet_terminate = 1;
		break;
	default:
		break;
	}	
	printf("signal handler.\n");
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

