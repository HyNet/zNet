
/*
 * Copyright (C) zhao
 */


#include<znet_core.h>


extern char **environ;
static char *znet_os_argv_last;


znet_int_t 
znet_init_setproctitle(void)
{
	char	*p;
	size_t	size;
	znet_uint_t i;

	size = 0;
	for (i = 0; environ[i]; i++) {
		size += strlen(environ[i]) + 1;
	}
	p = malloc(size);
	if (p == NULL) {
		return -1;
	}
	
	znet_os_argv_last = znet_os_argv[0];

    for (i = 0; znet_os_argv[i]; i++) {
        if (znet_os_argv_last == znet_os_argv[i]) {
            znet_os_argv_last = znet_os_argv[i] + strlen(znet_os_argv[i]) + 1;
        }
    }

    for (i = 0; environ[i]; i++) {
        if (znet_os_argv_last == environ[i]) {

            size = strlen(environ[i]) + 1;
            znet_os_argv_last = environ[i] + size;

            strncpy(p, environ[i], size);
            environ[i] = (char *) p;
            p += size;
        }
    }

    znet_os_argv_last--;		
	return 0;
}

void znet_setproctitle(char *title)
{
	char *p;
	znet_os_argv[1] = NULL;
	//p = strncpy(znet_os_argv[0], "znet:", znet_os_argv_last - znet_os_argv[0]);
	p = znet_strncpy(znet_os_argv[0], "znet:", znet_os_argv_last - znet_os_argv[0]);
	p = strncpy(p, title, znet_os_argv_last - p);
	p = znet_strncpy(p, title, znet_os_argv_last - p);
	
	if (znet_os_argv_last - p) {
        memset(p, ZNET_SETPROCTITLE_PAD, znet_os_argv_last - p);
    }
	return;
}

