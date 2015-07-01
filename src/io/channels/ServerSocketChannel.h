#ifndef ZNET_IO_CHANNELS_SERVERSOCKETCHANNEL_HEAD_
#define ZNET_IO_CHANNELS_SERVERSOCKETCHANNEL_HEAD_

#include"../../net/InetSocketAddress.h"
//#include"SelectionKey.h"

namespace zNet{
/*
 * A listening socket  
 *
 */
class ServerSocketChannel{

public:
    ServerSocketChannel();
    ~ServerSocketChannel();
private:
    int ServerSocketfd;
public:
    bool Bind(InetSocketAddress& local, int backlog = 65535);
	int Accept();
	//SelectionKey& regist()
	inline int getSockfd(){return ServerSocketfd;}
    
};

}

#endif //ZNET_IO_CHANNELS_SERVERSOCKETCHANNEL_HEAD_
