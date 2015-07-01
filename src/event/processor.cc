#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<iostream>
#include"processor.h"
#include<string.h>

zNet::event::processor::processor(int connfd)
		: connfd(connfd)
{
	fcntl(connfd, F_SETFL, fcntl(connfd, F_GETFL, 0) | O_NONBLOCK);
	process_loop = ev_loop_new(EVFLAG_AUTO);
	io_processor.set<processor, &processor::cb_processor>(this);
	io_processor.set(process_loop);
	io_processor.set(connfd, ev::READ);
	//std::cout << "--->process fd: "<< io_processor.fd << std::endl;
}

zNet::event::processor::~processor()
{
	//std::cout << "--->close fd: "<< io_processor.fd << std::endl;
	close(io_processor.fd);
	io_processor.stop();
	ev_break(process_loop, EVBREAK_ALL);
}

void zNet::event::processor::setconnfd(int connfd)
{
	io_processor.set(connfd, ev::READ|ev::WRITE);
}


void zNet::event::processor::cb_processor(ev::io&processor, int events)
{
	//std::cout << "cb_processor" << std::endl;
	if (events & EV_ERROR){
		std::cout << "invalid events" << std::endl;
		return;
	}
	if (events & EV_READ){
		std::cout << "["<< io_processor.fd <<"] "<<"read event" << std::endl;
		read_processor();
	}
	if (events & EV_WRITE){
		std::cout << "["<< io_processor.fd << "] "  <<"write event" << std::endl;
		write_processor();
	}
}

void zNet::event::processor::read_processor()
{
	//std::cout << "read_processor" << std::endl;
	char buf[1024];
	bzero(buf, sizeof(buf));
	ssize_t nread = recv(io_processor.fd, buf, sizeof(buf), 0);
	if (nread < 0) {
		std::cout << "read return < 0" << std::endl;
		return;
	}
	if (0 == nread) {
		std::cout << "read return 0" << std::endl;
		close(io_processor.fd);
		return;
	}
	setconnfd(io_processor.fd);
	//std::cout << "read bytes: " << nread << std::endl; 
	//std::cout << buf << std::endl;
	//write_processor();

}

void zNet::event::processor::write_processor()
{
	//std::cout << "write_processor" << std::endl;
	char buf[1024];
	bzero(buf, sizeof(buf));
	buf[0] = 'o';
	buf[1] = 'k';
	ssize_t nwrite = send(io_processor.fd, buf, sizeof(buf),0);
	if (nwrite < 0)
		return;
	//std::cout << buf <<std::endl;
	io_processor.stop();
	ev_break(process_loop, EVBREAK_ALL);
}
