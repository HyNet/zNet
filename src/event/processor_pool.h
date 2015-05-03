#ifndef ZNET_EVENT_PROCESSOR_POOL_HEAD_H_
#define ZNET_EVENT_PROCESSOR_POOL_HEAD_H_

#include<thread>
#include"processor.h"
#include"../util/blockqueue.h"

#define MAX_THREAD_NUM 64
namespace zNet{namespace event{

class processor_pool{
public:
	processor_pool(zNet::util::blockqueue<std::shared_ptr<zNet::event::processor>>& bq)
			: connfdqueue(bq)
			, b_stop_all(false)
	{
	}
	~processor_pool(){}

public:
	void stopall(){b_stop_all = true;}
	void startall(){
		for(int i=0; i< MAX_THREAD_NUM; i++){
			std::cout << "--->thread pool" <<std::endl;
			task tsk(*this);
			std::thread th{tsk};
			std::cout << "thread pool" << std::endl;
			thread_pool[i] = std::move(th);
		}
	}
private:
	zNet::util::blockqueue<std::shared_ptr<zNet::event::processor>>& connfdqueue;
	class task{
	public:
		task(processor_pool& pro_pool): proc_pool(pro_pool){}
		~task(){}
		void operator()(){
			while(!proc_pool.b_stop_all){
				std::shared_ptr<zNet::event::processor> p_processor;
				p_processor = proc_pool.connfdqueue.get();
				p_processor->start_loop();
			}
		}
	private:
		processor_pool& proc_pool;
	};
	bool b_stop_all;
	std::thread thread_pool[MAX_THREAD_NUM];
};

}}


#endif //ZNET_EVENT_PROCESSOR_POOL_HEAD_H_



