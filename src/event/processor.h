#ifndef ZNET_EVENT_PROCESSOR_HEAD_H_
#define ZNET_EVENT_PROCESSOR_HEAD_H_

#include<ev++.h>
//#include"../util/blockqueue.h"
#include<iostream>

namespace zNet{namespace event{

class processor{
public:
	processor(int connfd);
	~processor();
	processor(const processor&) = delete;
	const processor& operator= (const processor&) = delete;
public:
	void start_loop(){io_processor.start();io_processor.loop.run(0);}
private:
	void setconnfd(int connfd);
	void cb_processor(ev::io& processor, int events);
	void read_processor();
	void write_processor();
private:
	int connfd;
	ev::io 		io_processor;
	struct ev_loop * process_loop;

};

}}

#endif //ZNET_EVENT_PROCESSOR_HEAD_H_





