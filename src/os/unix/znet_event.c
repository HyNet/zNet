
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>
#include<znet_event.h>


static znet_int_t znet_epoll_add_event(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
static znet_int_t znet_epoll_del_event(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
static znet_int_t znet_epoll_process_events(znet_uint_t flags);

znet_event_actions_t   znet_event_actions = {
			znet_epoll_add_event,
			znet_epoll_del_event,
			znet_epoll_process_events
};


static znet_int_t 
znet_epoll_add_event(znet_event_t *ev, znet_int_t event, znet_uint_t flags)
{
	return 0;
}

static znet_int_t 
znet_epoll_del_event(znet_event_t *ev, znet_int_t event, znet_uint_t flags)
{
	return 0;
}

static znet_int_t 
znet_epoll_process_events(znet_uint_t flags)
{
	return 0;
}
