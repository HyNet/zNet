#ifndef ZNET_IO_CHANNELS_SELECTOR_HEAD_
#define ZNET_IO_CHANNELS_SELECTOR_HEAD_

#include<sys/epoll.h>
#include"SelectionKey.h"

namespace zNet{

#define MAXEVENTS 64

class Selector{
public:
	Selector();
	~Selector();
	Selector(const Selector&) = delete;
	Selector& operator=(const Selector&) = delete;
public:
	// wait forever
	int Select();
	// default: do not wait at all
	// or: x miliseconds
	int Select(long timeout = 0);
private:
	int efd;
	struct epoll_event events[MAXEVENTS];
public:
	inline int getSelector(){return efd;}
	bool isReadable(const SelectionKey& key);

};

} //zNet



#endif //ZNET_IO_CHANNELS_SELECTOR_HEAD_





