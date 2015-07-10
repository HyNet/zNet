
/*
 * Copyright zhao
 */

#include<znet.h>
#include<znet_core.h>

static znet_int_t znet_get_options(int argc, char *const *argv);
static znet_int_t znet_create_pidfile(void);
static znet_int_t znet_signal_process(char *sig);
static znet_int_t znet_save_argv(int argc, char *const *argv);

//static void znet_master_process_cycle(void);

static znet_uint_t		znet_show_help;
static znet_uint_t		znet_show_version;
static char				*znet_signal;

static char const *znet_help_words = " \
Usage: nginx [-?h] [-s signal]\n\n \
Options:\n \
	-?,-h              :print help message\n \
	-s signal          :send signal to a master process:stop\n \
";


int main(int argc, char** argv)
{
	if (znet_get_options(argc, argv) != 0)
		return 1;
	if (znet_show_help){
		printf(znet_help_words);
		return 0;
	}
	if (znet_signal) {
		return znet_signal_process(znet_signal);
	}
	znet_pid = getpid();
	znet_save_argv(argc, argv);
	znet_create_pidfile();
	znet_init_signals();
	znet_master_process_cycle();
	return 0;	
}


static znet_int_t znet_get_options(int argc, char *const *argv)
{
	char *p;
	int i;

	for(i = 1; i < argc; i++) {
		p = (char *)argv[i];
		
		if(*p++ != '-') {
			return -1;
		}

		while(*p) {
				switch (*p++) {
					case '?':
					case 'h':
						// help
						znet_show_help    = 1;
						znet_show_version = 1;
						break;
					case 's':
						// signal
						if(*p){
							znet_signal = (char *)p;
						} else if (argv[++i]){
							znet_signal = argv[i];
						} else {
							return -1;
						}
						
						if (strcmp(znet_signal, "stop") == 0) {
							// stop signal
							return 0;
						}
						// error signal name input
						return -1;
					default:
						// error
						return -1;
				}
		}
	}
	
	return 0;
}

znet_int_t 
znet_create_pidfile(void)
{
	char pid[1024];
	int len = 0;
	len = snprintf(pid, sizeof(pid), "%d", znet_pid);
	printf("%d\n",len);
	int fd = open("znetpid", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (write(fd, pid, len) == -1 ){
		return -1;
	}
	close(fd);
	return 0;
}

znet_int_t 
znet_signal_process(char *sig)
{
	znet_int_t pid;
	char buf[1024];

	int fd = open("znetpid", O_RDONLY, 0644);
	ssize_t n = read(fd, buf, 1024);
	close(fd);
	if ( n == -1)
		return 0;
	pid = atoi(buf);
	
	return znet_os_signal_process(sig,pid);
}


znet_int_t 
znet_save_argv(int argc, char *const *argv)
{
	znet_os_argv = (char **)argv;
	znet_argc = argc;
	return 0;
}

/*
static void znet_master_process_cycle(void)
{
	sigset_t	set;
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
	sigaddset(&set, znet_signal_value(ZNET_SHUTDOWN_SIGNAL));
	sigaddset(&set, znet_signal_value(ZNET_CHANGEBIN_SIGNAL));
	//sigaddset(&set, SIGWINCH);
	//sigaddset(&set, SIGTERM);
	//sigaddset(&set, SIGQUIT);
	//sigaddset(&set, SIGXCPU);
	
	sigprocmask(SIG_BLOCK, &set, NULL);
	sigemptyset(&set);

	//char *title = "master process";
	//setproctitle("%s", title);

	unsigned int delay = 0;
	
	for(;;){
		itv.it_interval.tv_sec = 0;
		itv.it_interval.tv_usec = 0;
		itv.it_value.tv_sec = delay / 1000;
		itv.it_value.tv_usec = ( delay % 1000 ) * 1000;
		setitimer(ITIMER_REAL, &itv, NULL);
		printf("cycle....\n");
		sigsuspend(&set);
		printf("cycle after signal...\n");
	}
}
*/
