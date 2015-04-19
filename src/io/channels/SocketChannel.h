#ifndef ZNET_IO_CHANNELS_SOCKETCHANNEL_HEAD_
#define ZNET_IO_CHANNELS_SOCKETCHANNEL_HEAD_

namespace zNet{

class SocketChannel{
public:
	SocketChannel();
	~SocketChannel();
private:
	int Socketfd;	
public:
	void open(int fd);
};

}

#endif //ZNET_IO_CHANNELS_SOCKETCHANNEL_HEAD_
