
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
static struct epoll_event *event_list;
static znet_uint_t nevents;

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
	int op;
	struct epoll_event ee;
	uint32_t	events, prev;
	znet_connection_t    *c;
	znet_event_t         *e;


	c = ev->data;
	
	events = (uint32_t)event;

	if(event == ZNET_READ_EVENT){
		e = c->write;
		prev = EPOLLOUT;
		
	}else{
		e = c->read;
		prev = EPOLLIN|EPOLLRDHUP;
	}
	
	if(e->active){
		op = EPOLL_CTL_MOD;
		events |= prev;
	}else{
		op = EPOLL_CTL_ADD;
	}	
	ee.events = events | (uint32_t) flags;
    ee.data.ptr = (void *) ((uintptr_t) c | ev->instance);

	if (epoll_ctl(ep, op, c->fd, &ee) == -1) {
		printf("epoll_ctl(%d, %d) failed\n", op, c->fd);
		return -1;
	}	
	ev->active = 1;
	return 0;
}

static znet_int_t 
znet_epoll_del_event(znet_event_t *ev, znet_int_t event, znet_uint_t flags)
{
	int op;
	uint32_t prev;
	znet_event_t *e;
	znet_connection_t *c;
	struct epoll_event ee;
	
	if (flags & ZNET_CLOSE_EVENT) {
        ev->active = 0;
        return 0;
    }

    c = ev->data;

    if (event == ZNET_READ_EVENT) {
        e = c->write;
        prev = EPOLLOUT;

    } else {
        e = c->read;
        prev = EPOLLIN|EPOLLRDHUP;
    }

    if (e->active) {
        op = EPOLL_CTL_MOD;
        ee.events = prev | (uint32_t) flags;
        ee.data.ptr = (void *) ((uintptr_t) c | ev->instance);

    } else {
        op = EPOLL_CTL_DEL;
        ee.events = 0;
        ee.data.ptr = NULL;
    }
	
	if (epoll_ctl(ep, op, c->fd, &ee) == -1) {
        printf("epoll_ctl(%d, %d) failed", op, c->fd);
        return -1;
    }

    ev->active = 0;

	return 0;
}

static znet_int_t 
znet_epoll_process_events(znet_uint_t flags)
{
	int events;
	int err;
	uint32_t revents;
	znet_int_t instance, i;
	znet_connection_t *c;
	znet_event_t *rev, *wev;
	// block
	events = epoll_wait(ep, event_list, (int) nevents, -1);
	err = (events == -1)? errno: 0;
	if (err) {
		printf("epoll wait failed\n");	
        return -1;
    }
	if (events == 0){
		printf("epoll wait failed, events is 0\n"); 
		return -1;
	}
	
	for(i = 0; i < events; i++){
		c = event_list[i].data.ptr;
	
		instance = (uintptr_t) c & 1;
        c = (znet_connection_t *) ((uintptr_t) c & (uintptr_t) ~1);
		
		rev = c->read;
		
		if (c->fd == -1 || rev->instance != instance) {
			continue;
		}
		
		revents = event_list[i].events;
		if (revents & (EPOLLERR|EPOLLHUP)) {
			printf("epoll wait failed\n");
		}
		
		if ((revents & (EPOLLERR|EPOLLHUP))
             && (revents & (EPOLLIN|EPOLLOUT)) == 0)
        {

            revents |= EPOLLIN|EPOLLOUT;
        }
		if ((revents & EPOLLIN) && rev->active) {
			rev->ready = 1;
			rev->handler(rev);
		}
		wev = c->write;

        if ((revents & EPOLLOUT) && wev->active) {

            if (c->fd == -1 || wev->instance != instance) {

                continue;
            }

            wev->ready = 1;

            wev->handler(wev);
        }
		
	}
	return 0;
}

static znet_int_t znet_epoll_init(void)
{
	if(ep == -1){
		ep = epoll_create(1024);
		if(ep == -1)
			return -1;	
	}
	if(event_list){
		free(event_list);
	}
	event_list = malloc(sizeof(struct epoll_event) * 1024);
	if(event_list == NULL)
		return -1;
	nevents = 1024;	

	return 0;
}

static void znet_epoll_done(void)
{
	
	if(close(ep) == -1){
		printf("close ep failed\n");
	}
	ep = -1;
	free(event_list);
	nevents = 0;
}

