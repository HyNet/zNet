#ifndef ZNET_EVENT_PROCESSOR_POOL_HEAD_H_
#define ZNET_EVENT_PROCESSOR_POOL_HEAD_H_

#include<thread>
#include<atomic>
#include<vector>
#include"processor.h"
#include"../util/blockqueue.h"

namespace zNet{namespace event{

class processor_pool{
public:
	processor_pool(zNet::util::blockqueue<std::unique_ptr<zNet::event::processor>>& bq)
			: connfdqueue(bq)
			, b_stop_all(false)
	{
	}
	~processor_pool(){
		b_stop_all = true;
		for (std::thread &th: thread_pool)
			th.join();
	}

public:
	void stopall(){b_stop_all = true;}
	void startall(){
		for(int i=0; i< std::thread::hardware_concurrency(); i++){
			std::cout << "--->thread pool" <<std::endl;
			task tsk(*this);
			std::thread th{tsk};
			std::cout << "thread pool" << std::endl;
			thread_pool.emplace_back(std::move(th));
		}
	}
private:
	zNet::util::blockqueue<std::unique_ptr<zNet::event::processor>>& connfdqueue;
	class task{
	public:
		task(processor_pool& pro_pool): proc_pool(pro_pool){}
		~task(){}
		void operator()(){
			while(!proc_pool.b_stop_all){
				std::unique_ptr<zNet::event::processor> p_processor;
				p_processor = std::move(proc_pool.connfdqueue.get());
				p_processor->start_loop();
			}
		}
	private:
		processor_pool& proc_pool;
	};
	std::atomic_bool b_stop_all;
	std::vector< std::thread> thread_pool;
};

}}


#endif //ZNET_EVENT_PROCESSOR_POOL_HEAD_H_



