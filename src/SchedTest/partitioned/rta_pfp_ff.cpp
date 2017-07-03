#include "rta_pfp_ff.h"
#include "iteration-helper.h"
#include "math-helper.h"

RTA_PFP_FF::RTA_PFP_FF():PartitionedSched(false, RTA, FIX_PRIORITY, NONE, "", "NONE") {}

RTA_PFP_FF::RTA_PFP_FF(TaskSet tasks, ProcessorSet processors, ResourceSet resources):PartitionedSched(false, RTA, FIX_PRIORITY, NONE, "", "NONE")
{
	this->tasks = tasks;
	this->processors = processors;
	this->resources = resources;

	this->resources.update(&(this->tasks));
	this->processors.update(&(this->tasks), &(this->resources));
	
	//this->tasks.RM_Order();
	this->processors.init();
}

ulong RTA_PFP_FF::interference(Task& task, ulong interval)
{
	return task.get_wcet() * ceiling((interval + task.get_jitter()), task.get_period());
}

ulong RTA_PFP_FF::response_time(Task& ti)
{
	//uint t_id = ti.get_id();
	ulong test_end = ti.get_deadline();
	ulong test_start = ti.get_total_blocking() + ti.get_wcet();
	ulong response = test_start;
	ulong demand = 0;
	while (response <= test_end)
	{
		demand = test_start;

		ulong total_interference = 0;

		foreach_higher_priority_task(tasks.get_tasks(), ti, th)
		{
			if (th->get_partition() == ti.get_partition())
			{
				total_interference += interference((*th), response);
			}
		}
		
		demand += total_interference;

		if (response == demand)
			return response + ti.get_jitter();
		else 
			response = demand;
	}
	return test_end + 100;
}

bool RTA_PFP_FF::alloc_schedulable()
{
	ulong response_bound;

	for (uint t_id = 0; t_id < tasks.get_taskset_size(); t_id ++)
	foreach(tasks.get_tasks(), ti)
	{
		if (ti->get_partition() == 0XFFFFFFFF)
			continue;
		
		response_bound = response_time((*ti));
		
		if (response_bound <= ti->get_deadline())
			ti->set_response_time(response_bound);
		else
			return false;
	}
	return true;
}

bool RTA_PFP_FF::is_schedulable()
{
	foreach(tasks.get_tasks(), ti)
	{
		if(!BinPacking_FF((*ti), tasks, processors, resources, TEST))
			return false;
	}
	return true;
}
