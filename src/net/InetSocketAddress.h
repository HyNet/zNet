#ifndef ZNET_NET_INETSOCKETADDRESS_HEAD_
#define ZNET_NET_INETSOCKETADDRESS_HEAD_

#include<netdb.h>
#include<string>
/*
 * encapsulation for socket address structure
 * protocol suit: IPv4, IPv6
 */


namespace zNet{

class InetSocketAddress{
public:
	InetSocketAddress();
	~InetSocketAddress();
	InetSocketAddress(const InetSocketAddress&) = delete;
	InetSocketAddress& operator= (const InetSocketAddress&) = delete;
private:
	struct addrinfo *result_;	
	struct addrinfo *curr;
	struct addrinfo hints;
	bool   bNeedRealse;
public:
	InetSocketAddress& TcpServMode();
	bool init(std::string hostname, std::string port);
	int getaifamily();
	int getsocktype();
	int getprotocol();
	sockaddr* getsockaddr();
	std::string getcanonname();
	socklen_t getsocklen();
	bool next();
	bool head();
};


}

#endif //ZNET_NET_INETSOCKETADDRESS_HEAD_
