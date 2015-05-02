#ifndef ZNET_NET_INETSOCKETADDRESS_HEAD_
#define ZNET_NET_INETSOCKETADDRESS_HEAD_

#include<netdb.h>
#include<string>

namespace zNet{

/*
 * encapsulation for socket address structure
 * protocol suit: IPv4, IPv6
 *
 *  Note: to truly construct InetSocketAddress, 
 *        remember to invoke init() after create 
 *        InetSoketAddress instance
 */
enum class SOCKMODE{TCPSERV, TCPCLIENT};

class InetSocketAddress{
public:
	/*
	 * Note: just a plain constructor, do nothing
	 * set mode functions and init functions must be called 
	 */
	InetSocketAddress();
	~InetSocketAddress();
	// delete copy and = constructor
	InetSocketAddress(const InetSocketAddress&) = delete;
	InetSocketAddress& operator= (const InetSocketAddress&) = delete;
private:
	struct addrinfo *result_;	
	struct addrinfo *curr;
	struct addrinfo hints;
	bool   bNeedRealse;
	// set mode to tcp server  
	void TcpServMode();
	// set mode to tcp client
	void TcpClientMode();
	//TODO: more mode need to be supported

public:
	/*
	 * initilize the InetSocketAddress
	 * @param hostname: a hostname or an address string. e.g "www.google.com" or "127.0.0.1"
	 * @param port: a service name or a decimal port number string. 
	 * @param mode: enum socket mode: SOCKET::TCPSERV,SOCKET::TCPCLIENT
	 */
	bool init(std::string hostname, std::string port, enum SOCKMODE mode = SOCKMODE::TCPSERV);

	int getaifamily() ;
	int getsocktype() ;
	int getprotocol() ;

	sockaddr* getsockaddr() ;
	std::string getcanonname() ;
	socklen_t getsocklen() ;

	bool next();
	bool head();
};


}

#endif //ZNET_NET_INETSOCKETADDRESS_HEAD_
