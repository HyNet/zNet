
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

int znet_init_signals(void)
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
