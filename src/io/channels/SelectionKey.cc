#include"SelectionKey.h"

using namespace zNet;

SelectionKey::SelectionKey(Selector& selector, ServerSocketChannel& channel, OP op)
		: selector_(selector)
		, channel_(channel)
		, op_(op)
{
	event_.data.fd = channel_.getSockfd();	
	setEpollEvent(&event_);
}

SelectionKey::~SelectionKey()
{
}

void SelectionKey::setEpollEvent(epoll_event* pevent)
{
	switch(op_){
		case OP::ACCEPT:
			event_.events = EPOLLIN;
			break;
		case OP::CONNECT:
			event_.events = EPOLLIN;
			break;
		case OP::READ:
			event_.events = EPOLLIN;
			break;
		case OP::WRITE:
			event_.events = EPOLLOUT;
			break;
		default:
			break;
	}
	epoll_ctl(selector_.getSelector(), EPOLL_CTL_ADD, event_.data.fd, &event_);
}
