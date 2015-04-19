#ifndef ZNET_IO_CHANNELS_SERVERSOCKETCHANNEL_HEAD_
#define ZNET_IO_CHANNELS_SERVERSOCKETCHANNEL_HEAD_

#include"../../net/InetSocketAddress.h"
#include"SocketChannel.h"

namespace zNet{

class ServerSocketChannel{

public:
    ServerSocketChannel();
    ~ServerSocketChannel();
private:
    int ServerSocketfd;
public:
    bool Bind(InetSocketAddress& local, int backlog = 65535);
	int Accept();
    
};

}

#endif //ZNET_IO_CHANNELS_SERVERSOCKETCHANNEL_HEAD_
