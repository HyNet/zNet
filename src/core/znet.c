
/*
 * Copyright zhao
 */

#include<znet.h>
#include<znet_core.h>

static int znet_get_options(int argc, char *const *argv);


static unsigned int		znet_show_help;
static unsigned int		znet_show_version;
static char				*znet_signal;

static char const *znet_help_words = "Usage: nginx [-?h] [-s signal]\n\n \
Options:\n \
	-?,-h              :print help message\n \
	-s signal          :send signal to a master process:stop\n";


int main(int argc, char** argv)
{
	if (znet_get_options(argc, argv) != 0)
		return 1;
	if (znet_show_help){
		printf(znet_help_words);
	}
	return 0;	
}


static int znet_get_options(int argc, char *const *argv)
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
