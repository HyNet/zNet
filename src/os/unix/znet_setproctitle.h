
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_SETPROCTITLE_H_INCLUDED_
#define _ZNET_SETPROCTITLE_H_INCLUDED_

#define ZNET_SETPROCTITLE_PAD '\0'

znet_int_t znet_init_setproctitle(void);
void znet_setproctitle(char *title);


#endif /*_ZNET_SETPROCTITLE_H_INCLUDED_*/
