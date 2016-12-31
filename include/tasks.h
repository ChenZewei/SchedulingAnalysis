#ifndef TASKS_H
#define TASKS_H

#include <algorithm>
#include <iostream>
#include "types.h"

using namespace std;

class Processor;
class ProcessorSet;
class Resource;
class ResourceSet;
class Param;
class Random_Gen;

typedef vector<fraction_t> Ratio;

class Request
{
	private:
		uint task_model = TPS_TASK_MODEL;
		uint resource_id;
		uint num_requests;
		ulong max_length;
		ulong total_length;
		uint locality;
	public:
		Request(uint resource_id,
			uint num_requests,
			ulong max_length,
			ulong total_length,
			uint locality = MAX_INT);

		uint get_resource_id() const;
		uint get_num_requests() const;
		ulong get_max_length() const;
		ulong get_total_length() const;
		ulong get_locality() const;
};

typedef vector<Request> Resource_Requests;
typedef vector<uint> CPU_Set;

class Task
{
	private:
		uint id;
		ulong wcet;
		ulong wcet_critical_sections;
		ulong wcet_non_critical_sections;
		ulong spin;
		ulong self_suspension;
		ulong local_blocking;
		ulong remote_blocking;
		ulong total_blocking;
		ulong jitter;
		ulong response_time;//initialization as WCET
		ulong deadline;
		ulong period;
		uint priority;
		uint partition;//0XFFFFFFFF
		uint cluster;
		CPU_Set* affinity;
		bool independent;
		bool carry_in;
		fraction_t utilization;
		fraction_t density;
		Ratio ratio;//for heterogeneous platform
		Resource_Requests requests;
	public:
		Task(	uint id,
			ulong wcet, 
			ulong period,
			ulong deadline = 0,
			uint priority = 0);

		Task(	uint id,
			ResourceSet& resourceset,
			Param param,
			ulong wcet, 
			ulong period,
			ulong deadline = 0,
			uint priority = 0);

		~Task();
		
		void init();

		uint task_model();

		uint get_id() const;
		void set_id(uint id);
		ulong get_wcet() const;
		ulong get_deadline() const;
		ulong get_period() const;
		bool is_feasible() const;

		Resource_Requests& get_requests();
		Request& get_request_by_id(uint id);
		bool is_request_exist(uint resource_id);

		ulong get_wcet_critical_sections() const;
		void set_wcet_critical_sections(ulong csl);
		ulong get_wcet_non_critical_sections() const;
		void set_wcet_non_critical_sections(ulong ncsl);
		ulong get_spin() const;
		void set_spin(ulong spining);
		ulong get_local_blocking() const;
		void set_local_blocking(ulong lb);
		ulong get_remote_blocking() const;
		void set_remote_blocking(ulong rb);
		ulong get_total_blocking() const;
		void set_total_blocking(ulong tb);
		ulong get_self_suspension() const;
		void set_self_suspension(ulong ss);
		ulong get_jitter() const;
		void set_jitter(ulong jit);
		ulong get_response_time() const;
		void set_response_time(ulong response);
		uint get_priority() const;
		void set_priority(uint prio);
		uint get_partition() const;
		void set_partition(uint cpu);
		uint get_cluster() const;
		void set_cluster(uint clu);
		CPU_Set* get_affinity() const;
		void set_affinity(CPU_Set* affi);
		bool is_independent() const;
		void set_dependent();
		bool is_carry_in() const;
		void set_carry_in();
		void clear_carry_in();

		void add_request(uint res_id, uint num, ulong max_len, ulong total_len, uint locality = MAX_INT);
		
		uint get_max_job_num(ulong interval); //max number of jobs in an arbitrary length of interval
		uint get_max_request_num(uint resource_id, ulong interval);
		ulong DBF(ulong interval);//Demand Bound Function
		void DBF();
		fraction_t get_utilization() const;
		fraction_t get_density() const;
		void get_utilization(fraction_t &utilization);
		void get_density(fraction_t &density);
};

typedef vector<Task> Tasks;

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
		~TaskSet();
		
		void init();

		void calculate_spin(ResourceSet& resourceset, ProcessorSet& processorset);
		void calculate_local_blocking(ResourceSet& resourceset);
		
		void add_task(long wcet, long period, long deadline = 0);
		void add_task(ResourceSet& resourceset, Param param, long wcet, long period, long deadline = 0);

		Tasks& get_tasks();
		Task& get_task_by_id(uint id);

		bool is_implicit_deadline();
		bool is_constrained_deadline();
		bool is_arbitary_deadline();
		uint get_taskset_size() const ;

		fraction_t get_task_utilization(uint index) const;
		fraction_t get_task_density(uint index) const;
		ulong get_task_wcet(uint index) const;
		ulong get_task_deadline(uint index) const;
		ulong get_task_period(uint index) const;
		
		fraction_t get_utilization_sum() const;
		fraction_t get_utilization_max() const;
		fraction_t get_density_sum() const;
		fraction_t get_density_max() const;
		void get_utilization_sum(fraction_t &utilization_sum) const;
		void get_utilization_max(fraction_t &utilization_max) const;
		void get_density_sum(fraction_t &density_sum) const;
		void get_density_max(fraction_t &density_max) const;

		void sort_by_period();//increase
		void sort_by_utilization();//decrease
		void RM_Order();
		ulong DBF(ulong time);

		void display();

};

typedef struct ArcNode
{
	uint tail;//i
	uint head;//j
}ArcNode,*ArcPtr;

typedef struct VNode
{
	uint job_id;
	uint type;
	uint pair;
	ulong wcet;
	ulong deadline;
	uint level;
	vector<ArcPtr> precedences;
	vector<ArcPtr> follow_ups;
}VNode,*VNodePtr;

typedef struct 
{
	vector<VNode> v;
	vector<ArcNode> a;
}Graph;

class DAG_Task:public Task
{
	private:
		uint task_model = DAG_TASK_MODEL;
		uint task_id;
		vector<VNode> vnodes;
		vector<ArcNode> arcnodes;
		ulong vol;//total wcet of the jobs in graph
		ulong len;
		ulong deadline;
		ulong period;
		fraction_t utilization;
		fraction_t density;
		uint vexnum;
		uint arcnum;
		ulong spin;
		ulong self_suspension;
		ulong local_blocking;
		ulong remote_blocking;
		ulong total_blocking;
		ulong jitter;
		ulong response_time;//initialization as WCET
		uint priority;
		uint partition;//0XFFFFFFFF
		Ratio ratio;//for heterogeneous platform
		Resource_Requests requests;
	public:
		DAG_Task(uint task_id, ulong period, ulong deadline = 0, uint priority = 0);
		DAG_Task(	uint task_id,
					ResourceSet& resourceset,
					Param param,
					ulong wcet, 
					ulong period,
					ulong deadline = 0,
					uint priority = 0);
		void graph_gen(vector<VNode> &v, vector<ArcNode> &a, Param param, uint n_num, double arc_density = 0.6);
		void sub_graph_gen(vector<VNode> &v, vector<ArcNode> &a, uint n_num, int G_TYPE = G_TYPE_P);
		void sequential_graph_gen(vector<VNode> &v, vector<ArcNode> &a, uint n_num);
		void graph_insert(vector<VNode> &v, vector<ArcNode> &a, uint replace_node);

		uint task_model();		
		
		uint get_id() const;
		void set_id(uint id);
		uint get_vnode_num() const;
		uint get_arcnode_num() const;

		vector<VNode>& get_vnodes();
		VNode& get_vnode_by_id(uint job_id);
		ulong get_deadline() const;
		ulong get_period() const;
		ulong get_vol() const;
		ulong get_len() const;
		fraction_t get_utilization() const;
		fraction_t get_density() const;
		void add_job(ulong wcet, ulong deadline = 0);
		void add_job(vector<VNode> &v, ulong wcet, ulong deadline = 0);
		void add_arc(uint tail, uint head);
		void add_arc(vector<ArcNode> &a, uint tail, uint head);
		void delete_arc(uint tail, uint head);
		void refresh_relationship();
		void refresh_relationship(vector<VNode> &v, vector<ArcNode> &a);
		void update_vol();
		void update_len();
		bool is_acyclic();
		uint DBF(uint time);//Demand Bound Function
		void DBF();
		void get_utilization(fraction_t &utilization);
		void get_density(fraction_t &density);
				
		

		ulong DFS(VNode vnode);//Depth First Search
		ulong BFS(VNode vnode);//Breath First Search

		bool is_arc_exist(uint tail, uint head);
		bool is_arc_exist(const vector<ArcNode> &a, uint tail, uint head);
		
		void display_vertices();
		void display_vertices(vector<VNode> v);
		void display_arcs();
		void display_arcs(vector<ArcNode> a);
		void display_follow_ups(uint job_id);
		void display_precedences(uint job_id);
		uint get_indegrees(uint job_id) const;
		uint get_outdegrees(uint job_id) const;
};

typedef vector<DAG_Task> DAG_Tasks;

class DAG_TaskSet
{
	private:
		DAG_Tasks dag_tasks;
		fraction_t utilization_sum;
		fraction_t utilization_max;
		fraction_t density_sum;
		fraction_t density_max;
	public:
		DAG_TaskSet();
		~DAG_TaskSet();

		void add_task(ResourceSet& resourceset, Param param, long wcet, long period, long deadline = 0);
		void add_task(DAG_Task dag_task);

		DAG_Tasks& get_tasks();
		DAG_Task& get_task_by_id(uint id);
		uint get_taskset_size() const ;
		
		fraction_t get_utilization_sum() const;
		fraction_t get_utilization_max() const;
		fraction_t get_density_sum() const;
		fraction_t get_density_max() const;

		void sort_by_period();		
};

void tast_gen(TaskSet& taskset, ResourceSet& resourceset, Param param, double utilization);

void dag_task_gen(DAG_TaskSet& dag_taskset, ResourceSet& resourceset, Param param, double utilization);
ulong gcd(ulong a, ulong b);
ulong lcm(ulong a, ulong b);


#endif
