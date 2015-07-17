
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_EVENT_H_INCLUDED_
#define _ZNET_EVENT_H_INCLUDED_

#include<znet_core.h>

typedef struct {
	void *data;
}znet_event_t;

typedef struct {
	znet_int_t (*add)(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
	znet_int_t (*del)(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
	znet_int_t (*process_events)(znet_uint_t flags);
}znet_event_actions_t;

extern znet_event_actions_t znet_event_actions;

#define znet_process_events   znet_event_actions.process_events

#define znet_add_event        znet_event_actions.add
#define znet_del_event        znet_event_actions.del

#endif /*_ZNET_EVENT_H_INCLUDED_*/
