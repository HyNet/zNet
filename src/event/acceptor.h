#ifndef ZNET_EVENT_ACCEPTOR_HEAD_H_
#define ZNET_EVENT_ACCEPTOR_HEAD_H_

#include<ev++.h>
#include"../io/channels/ServerSocketChannel.h"
#include"../util/blockqueue.h"
#include"processor.h"
#include<memory>

#define MAX_ACCEPTOR_QUEUE 64

namespace zNet{namespace event{

class acceptor{
public:
	acceptor(ServerSocketChannel& ssChannel, util::blockqueue<std::shared_ptr<processor>>& bq);
	~acceptor();
	acceptor(const acceptor&) = delete;
	acceptor& operator= (const acceptor&) = delete;
public:
	void start_loop(){io_accept.loop.run(0);}
private:
	void cb_accept(ev::io& io_accept, int events);
private:
	ev::io 		io_accept;
	struct ev_loop* accept_loop;
	ServerSocketChannel& ssChannel;
	util::blockqueue<std::shared_ptr<processor>>& processor_queue;
};

}}

#endif //ZNET_EVENT_ACCEPTOR_HEAD_H_





