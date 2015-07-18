
/*
 * Copyright (C) zhao
 */

#include<znet_core.h>
#include<znet_event.h>


static znet_int_t znet_epoll_add_event(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
static znet_int_t znet_epoll_del_event(znet_event_t *ev, znet_int_t event, znet_uint_t flags);
static znet_int_t znet_epoll_process_events(znet_uint_t flags);
static znet_int_t znet_epoll_init(void);
static void znet_epoll_done(void);

static int ep = -1;

znet_event_actions_t   znet_event_actions = {
			znet_epoll_add_event,
			znet_epoll_del_event,
			znet_epoll_process_events,
			znet_epoll_init,
			znet_epoll_done
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

static znet_int_t znet_epoll_init(void)
{
	if(ep == -1){
		ep = epoll_create(1024);
		if(ep == -1)
			return -1;	
	}
	
	return 0;
}

static void znet_epoll_done(void)
{
	
	close(ep);
	ep = -1;
}
