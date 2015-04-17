#ifndef ZNET_IO_CHANNELS_SELECTIONKEY_HEAD_
#define ZNET_IO_CHANNELS_SELECTIONKEY_HEAD_

namespace zNet{

enum class OP{ACCEPT,CONNECT,READ,WRITE};

class SelectionKey{
public:
	SelectionKey();
	~SelectionKey();
	SelectionKey(const SelectionKey&) = delete;
	SelectionKey(SelectionKey&&) = delete;
	SelectionKey& operator=(const SelectionKey&) = delete;
public:
	static const OP OP_ACCEPT 	= OP::ACCEPT;
	static const OP OP_CONNECT 	= OP::CONNECT;
	static const OP OP_READ 	= OP::READ;
	static const OP OP_WRITE 	= OP::WRITE;
};

}

#endif //ZNET_IO_CHANNELS_SELECTIONKEY_HEAD_
