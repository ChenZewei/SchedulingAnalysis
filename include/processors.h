#ifndef PROCESSORS_H
#define PROCESSORS_H
#include <vector>
#include <list>
#include "tasks.h"
#include "types.h"

using namespace std;

typedef list<uint> TaskQueue;//之所以用list是因为list是双向链表，适合增删比较频繁的情况

class Processor
{
	private:
		TaskQueue queue;

		fraction_t speedfactor;
		fraction_t utilization;
		fraction_t density;
	public:
		Processor(fraction_t speedfactor = 1)
		{
			speedfactor = speedfactor;
			utilization = 0;
			density = 0;
		}
		
		fraction_t get_speedfactor()
		{
			return speedfactor;
		}
		fraction_t get_utilization()
		{
			return utilization;
		}
		fraction_t get_density()
		{
			return density;
		}
		void update(TaskSet taskset)
		{	
			utilization = 0;
			list<uint>::iterator it = queue.begin();
			density = 0;
			for(; it != queue.end(); it++)
			{
				utilization += taskset.get_task_utilization(*it);
				density += taskset.get_task_density(*it);
			}
		}

		void add_task(TaskSet taskset, uint id);
		void remove_task(TaskSet taskset, uint id);
		
	
};

typedef vector<Processor> Processors;

class ProcessorSet
{
	private:
		Processors processors;
	public:
		ProcessorSet(uint num)//for identical multiprocessor platform
		{
			for(int i = 0; i < num; i++)
				processors.push_back(Processor());
		}

		uint get_processor_num()
		{
			return processors.size();
		}
};
#endif
