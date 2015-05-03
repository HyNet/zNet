#ifndef ZNET_IO_CHANNELS_SOCKETCHANNEL_HEAD_
#define ZNET_IO_CHANNELS_SOCKETCHANNEL_HEAD_

#include"../../net/InetSocketAddress.h"

namespace zNet{

class SocketChannel{
public:
	SocketChannel();
	~SocketChannel();
private:
	int Socketfd;	
public:
	bool Connect(InetSocketAddress& addr);
};

}

#endif //ZNET_IO_CHANNELS_SOCKETCHANNEL_HEAD_
