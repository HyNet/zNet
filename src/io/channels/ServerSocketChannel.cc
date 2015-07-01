#include<sys/socket.h>
#include <fcntl.h>
#include<unistd.h>
#include"ServerSocketChannel.h"

using namespace zNet;

ServerSocketChannel::ServerSocketChannel()
		: ServerSocketfd(-1)
{
}

ServerSocketChannel::~ServerSocketChannel()
{
	if (ServerSocketfd > 0)
		close(ServerSocketfd);
}

bool ServerSocketChannel::Bind( InetSocketAddress& local, int backlog/*=65535*/)
{
	ServerSocketfd = socket(local.getaifamily(), local.getsocktype(), local.getprotocol());	
	if (ServerSocketfd < 0)
		return false;
	if (0 != bind(ServerSocketfd, local.getsockaddr(), local.getsocklen()))
		return false;
	fcntl(ServerSocketfd, F_SETFL, fcntl(ServerSocketfd, F_GETFL, 0) | O_NONBLOCK);
	if (0 != listen(ServerSocketfd, backlog))
		return false;
	return true;
}

int ServerSocketChannel::Accept()
{
	struct sockaddr_storage cliaddr;
	socklen_t len = sizeof(cliaddr);
	if (ServerSocketfd < 0)
		return -1;
	return accept(ServerSocketfd, (struct sockaddr*)&cliaddr,&len);	
}
