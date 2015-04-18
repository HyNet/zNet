#include"SocketChannel.h"
#include<unistd.h>

using namespace zNet;

SocketChannel::SocketChannel()
		: Socketfd(-1)
{
}

SocketChannel::~SocketChannel()
{
	if (Socketfd > 0)
		close(Socketfd);
}

void SocketChannel::open(int fd)
{
	Socketfd = fd;
}

