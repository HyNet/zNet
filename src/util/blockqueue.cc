#include"blockqueue.h"
#include<stdio.h>

template<typename T>
void zNet::util::blockqueue<T>::put(const T& val)
{
	//TODO
	std::lock_guard<std::mutex> lck(mtx);
	queue.push_back(val);
	cond.notify_one();
}

/*
template<typename T>
void zNet::util::blockqueue<T>::put(T val)
{
	//TODO
	std::lock_guard<std::mutex> lck(mtx);
	queue.push_back(val);
	cond.notify_one();
}
*/
template<typename T>
void zNet::util::blockqueue<T>::put(T&& val)
{
	//TODO
	std::lock_guard<std::mutex> lck(mtx);
	queue.push_back(val);
	cond.notify_one();
}

template<typename T>
T zNet::util::blockqueue<T>::get()
{
	//TODO
	std::unique_lock<std::mutex> lck(mtx);
	cond.wait(lck,[this]{return !queue.empty();});
	T val{ queue.front()};
	queue.pop_front();
	return val;
}





