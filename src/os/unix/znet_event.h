
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_EVENT_H_INCLUDED_
#define _ZNET_EVENT_H_INCLUDED_

#include<znet_core.h>

typedef struct {
	void *data;
	unsigned instance:1;
	unsigned active:1;
}znet_event_t;

typedef struct {
	znet_int_t (*add)(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
	znet_int_t (*del)(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
	znet_int_t (*process_events)(znet_uint_t flags);
	znet_int_t  (*init)(void);
	void (*done)(void);
}znet_event_actions_t;

extern znet_event_actions_t znet_event_actions;

#define ZNET_READ_EVENT     (EPOLLIN|EPOLLRDHUP)
#define ZNET_WRITE_EVENT    EPOLLOUT
#define  ZNET_CLOSE_EVENT 1

#define znet_process_events   znet_event_actions.process_events

#define znet_add_event        znet_event_actions.add
#define znet_del_event        znet_event_actions.del

#endif /*_ZNET_EVENT_H_INCLUDED_*/
