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

};

}

#endif //ZNET_IO_CHANNELS_SELECTIONKEY_HEAD_
