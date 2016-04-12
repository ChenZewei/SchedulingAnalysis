#ifndef TASKS_H
#define TASKS_H

#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "types.h"
using namespace std;

typedef vector<fraction_t> Ratio;

class Task
{
	private:
		uint wcet;
		uint deadline;
		uint period;
		uint priority;
		fraction_t utilization;
		fraction_t density;
		Ratio ratio;//for heterogeneous platform
	public:
		Task(uint wcet, 
			uint period,
			uint deadline = 0,
			uint priority = 0);
		
		uint get_wcet()
		{
			return wcet;
		}
		uint get_deadline()
		{
			return deadline;
		}
		uint get_period()
		{
			return period;
		}
		bool is_feasible()
		{
			return deadline >= wcet && period >= wcet && wcet > 0;
		}
		
		uint DBF(uint time);//Demand Bound Function
		void DBF();
		fraction_t get_utilization();
		fraction_t get_density();
		void get_utilization(fraction_t &utilization);
		void get_density(fraction_t &density);
	
};

typedef vector<Task> Tasks;

#define foreach(tasks, condition) \
		for(int i; i < tasks.size(); i++)	\
		{									\
			if(condition)					\
				return false;				\
		}

class TaskSet
{
	private:
		Tasks tasks;
		
		fraction_t utilization_sum;
		fraction_t utilization_max;
		fraction_t density_sum;
		fraction_t density_max;
	public:
		TaskSet();
		void add_task(uint wcet, uint period, uint deadline = 0)
		{
			fraction_t utilization_new = wcet, density_new = wcet;
			utilization_new /= period;
			if(0 == deadline)
				density_new /= period;
			else
				density_new /= min(deadline, period);
			tasks.push_back(Task(wcet, period, deadline));
			utilization_sum += utilization_new;
			density_sum += density_new;
			if(utilization_max < utilization_new)
				utilization_max = utilization_new;
			if(density_max < density_new)
				density_max = density_new;
		}
		bool is_implicit_deadline()
		{
			foreach(tasks,tasks[i].get_deadline() != tasks[i].get_period());
			return true;
		}
		bool is_constraint_deadline()
		{
			foreach(tasks,tasks[i].get_deadline() > tasks[i].get_period());
			return true;
		}
		bool is_arbitary_deadline()
		{
			return !(is_implicit_deadline())&&!(is_constraint_deadline());
		}
		uint get_taskset_size()
		{
			return tasks.size();
		}
		
		fraction_t get_utilization_sum();
		fraction_t get_utilization_max();
		fraction_t get_density_sum();
		fraction_t get_density_max();
		void get_utilization_sum(fraction_t &utilization_sum);
		void get_utilization_max(fraction_t &utilization_max);
		void get_density_sum(fraction_t &density_sum);
		void get_density_max(fraction_t &density_max);

		uint DBF(uint time);
};
#endif
