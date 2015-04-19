#include<string.h>
#include"InetSocketAddress.h"

using namespace zNet;

InetSocketAddress::InetSocketAddress()
		: result_(NULL)
		, curr(NULL)
		, bNeedRealse(false)
{
	memset(&hints, 0, sizeof(struct addrinfo));
}

InetSocketAddress::~InetSocketAddress()
{
	if (bNeedRealse)
		freeaddrinfo(result_);
	result_ = NULL;
	curr = NULL;
}

bool InetSocketAddress::init(std::string hostname, std::string port)
{
	if (0 != getaddrinfo(hostname.c_str(), port.c_str(), &hints, &result_)){
		return false;
	}
	bNeedRealse = true;
	curr = result_;

	//TODO
	return true;
}

InetSocketAddress& InetSocketAddress::TcpServMode()
{
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	return *this;
}

int InetSocketAddress::getaifamily()
{
	if (!bNeedRealse)
		return -1;
	return curr->ai_family;
}

int InetSocketAddress::getsocktype()
{
	if (!bNeedRealse)
		return -1;
	return curr->ai_socktype;
}

int InetSocketAddress::getprotocol()
{
	if (!bNeedRealse)
		return -1;
	return curr->ai_protocol;
}

sockaddr* InetSocketAddress::getsockaddr()
{
	//TODO
	if (!bNeedRealse)
		return NULL;
	return curr->ai_addr;
}

socklen_t InetSocketAddress::getsocklen()
{
	if (!bNeedRealse)
		return -1;
	return curr->ai_addrlen;
}

bool InetSocketAddress::next()
{
	if (NULL == curr->ai_next)
		return false;
	curr = curr->ai_next;
	return true;
}

bool InetSocketAddress::head()
{
	if (NULL == result_)
		return false;
	curr = result_;
	return true;	
}
