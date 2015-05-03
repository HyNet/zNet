#ifndef ZNET_IO_CHANNELS_SELECTIONKEY_HEAD_
#define ZNET_IO_CHANNELS_SELECTIONKEY_HEAD_

#include<sys/epoll.h>

#include"Selector.h"
#include"ServerSocketChannel.h"

namespace zNet{

enum class OP{ACCEPT,CONNECT,READ,WRITE};

class SelectionKey{
public:
	SelectionKey(Selector& selector, ServerSocketChannel& channel, OP op);
	~SelectionKey();
	SelectionKey(const SelectionKey&) = delete;
	SelectionKey(SelectionKey&&) = delete;
	SelectionKey& operator=(const SelectionKey&) = delete;
public:
	static const OP OP_ACCEPT 	= OP::ACCEPT;
	static const OP OP_CONNECT 	= OP::CONNECT;
	static const OP OP_READ 	= OP::READ;
	static const OP OP_WRITE 	= OP::WRITE;
	
private:
	Selector& selector_;
	ServerSocketChannel& channel_;
	OP op_;
	epoll_event event_;
	
	void setEpollEvent(epoll_event* pevent);
public:
	bool isReadable(){return selector_.isReadable(this);}
};

}

#endif //ZNET_IO_CHANNELS_SELECTIONKEY_HEAD_
