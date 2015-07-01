#ifndef ZNET_UTIL_BLOCKQUEUE_HEAD_H_
#define ZNET_UTIL_BLOCKQUEUE_HEAD_H_

#include<mutex>
#include<condition_variable>
#include<list>

namespace zNet{namespace util{

template<typename T>
class blockqueue {
public:
		blockqueue(){}
		~blockqueue(){}
		blockqueue(const blockqueue&) = delete;
		blockqueue& operator= (const blockqueue&) = delete;
public:
	void put(const T& val);
	//void put(T val);
	void put(T&& val);
	T get();
private:
	std::mutex mtx;
	std::condition_variable cond;
	std::list<T> queue;
};


}}

#include"blockqueue.cc"

#endif //ZNET_UTIL_BLOCKQUEUE_HEAD_H_





