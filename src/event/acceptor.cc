#include"acceptor.h"
#include<iostream>
#include<utility>
zNet::event::acceptor::acceptor(ServerSocketChannel& ssChannel, util::blockqueue<std::unique_ptr<processor>>& bq)
		: ssChannel(ssChannel)
		, processor_queue(bq)
{
	accept_loop = ev_loop_new(EVFLAG_AUTO);
	io_accept.set<acceptor, &acceptor::cb_accept>(this);
	io_accept.set(accept_loop);
	io_accept.start(ssChannel.getSockfd(), ev::READ);
}

zNet::event::acceptor::~acceptor()
{
}

void zNet::event::acceptor::cb_accept(ev::io& io_accept, int events)
{
	if (!(events & EV_READ))
		return;
	//std::cout << "cb_accept" << std::endl;
	int connfd = ssChannel.Accept();
	if (connfd < 0)
		return;
	//std::cout << "connfds in acceptorqueue: "<< connfd << std::endl;
	std::unique_ptr<processor> p_processor(new zNet::event::processor(connfd));
	processor_queue.put(std::move(p_processor));
	//std::cout << "put connfd to processor_queue" << std::endl;
}






