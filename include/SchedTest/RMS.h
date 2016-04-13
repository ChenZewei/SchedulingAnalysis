#ifndef RMS_H
#define RMS_H

#include <math.h>
#include <algorithm>
#include <iostream>

#include "../tasks.h"

using namespace std;

class RMS
{
	private:
		uint processor_num;
		uint task_num;
	public:
		RMS(uint p_num);
		bool is_uniprocessor();
		fraction_t get_utilization_bound(TaskSet taskset);
		bool is_RM_schedulable(TaskSet taskset);
		bool is_RM_schedulable(TaskSet taskset, Task task);
};
#endif
