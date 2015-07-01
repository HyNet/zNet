#include"SocketChannel.h"
#include<unistd.h>
#include<sys/socket.h>

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

bool SocketChannel::Connect( InetSocketAddress& addr)
{
	Socketfd = socket(addr.getaifamily(), addr.getsocktype(), addr.getprotocol());
	if (Socketfd < 0)
		return false;
	if (0 != connect(Socketfd, addr.getsockaddr(), addr.getsocklen()))
		return false;
	
	return true;
}
