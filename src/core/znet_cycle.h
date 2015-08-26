
/*
 * Copyright (C) zhao
 */

#ifndef _ZNET_CYCLE_H_INCLUDED_
#define _ZNET_CYCLE_H_INCLUDED_

#include<znet_core.h>

struct znet_cycle_s {
	znet_connection_t **files;
	znet_uint_t			files_n;
	znet_connection_t  *free_connections;
	znet_uint_t			free_connection_n;

	znet_array_t		listening;
	znet_list_t			open_files;

	znet_uint_t			connection_n;
	//znet_uint_t			files_n;
	
	znet_connection_t	*connections;
	znet_event_t		*read_events;
	znet_event_t		*write_events;
};

#endif /*_ZNET_CYCLE_H_INCLUDED_*/


