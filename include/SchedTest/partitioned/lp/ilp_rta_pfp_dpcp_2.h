#ifndef ILP_RTA_PFP_DPCP_2_H
#define ILP_RTA_PFP_DPCP_2_H

#include "types.h"
#include "varmapper.h"
#include "p_sched.h"
#include "tasks.h"
#include "processors.h"
#include "resources.h"

/*
|________________|_______________|_____________|_____________|_____________|____________|
|                |               |             |             |             |            |
|(63-45)Reserved |(44-40)var type|(39-30)part1 |(29-20)part2 |(19-10)part3 |(9-0)part4  |
|________________|_______________|_____________|_____________|_____________|____________|
*/

class ILPDPCPMapper_2: public VarMapperBase
{
	public:
		enum var_type
		{
			LOCALITY_ASSIGNMENT,//A_i_k Task i assign on processor k(k start from 1)
			RESOURCE_ASSIGNMENT,//Q_r_k resource r assign to processor x(k start from 1)
			SAME_TASK_LOCALITY,//U_i_x Task i and task x assigned on same processor
			SAME_RESOURCE_LOCALITY,//V_u_v resource u and resource v assigned on same processor
			SAME_TR_LOCALITY,//W_i_u task i and resource u assigned on same processor
			APPLICATION_CORE,//AP_k
			TASK_ONLY,//TO_i
			TASK_ONLY_PROCESSOR,//TO_i_K
			TBT_PREEMPT_NUM,//H_i_x
			RBT_PREEMPT_NUM,//H_i_x_v resource v is requested by task x
			RBR_PREEMPT_NUM,//H_i_x_u_v
			RESPONSE_TIME,//R_i
			BLOCKING_TIME,//B_i
			REQUEST_BLOCKING_TIME,//b_i_r
			INTERFERENCE_TIME_R,//IR_i
			INTERFERENCE_TIME_R_RESOURCE,//IR_i_u
			INTERFERENCE_TIME_C,//IC_i
			INTERFERENCE_TIME_C_TASK,//IC_i_x
		};
	private:
		static uint64_t encode_request(uint64_t type, uint64_t part_1 = 0, uint64_t part_2 = 0, uint64_t part_3 = 0, uint64_t part_4 = 0);
		static uint64_t get_type(uint64_t var);
		static uint64_t get_part_1(uint64_t var);
		static uint64_t get_part_2(uint64_t var);
		static uint64_t get_part_3(uint64_t var);
		static uint64_t get_part_4(uint64_t var);
	public:
		ILPDPCPMapper_2(uint start_var = 0);
		uint lookup(uint type, uint part_1 = 0, uint part_2 = 0, uint part_3 = 0, uint part_4 = 0);
		string var2str(unsigned int var) const;
		string key2str(uint64_t key) const;
};

////////////////////ILP_PFP_DPCP_2////////////////////

class ILP_RTA_PFP_DPCP_2: public PartitionedSched
{
	private:
		TaskSet tasks;
		ProcessorSet processors;
		ResourceSet resources;

		void construct_exp(ILPDPCPMapper_2& vars, LinearExpression *exp, uint type, uint part_1 = 0, uint part_2 = 0, uint part_3 = 0, uint part_4 = 0);
		void set_objective(LinearProgram& lp, ILPDPCPMapper_2& vars);
		void add_constraints(LinearProgram& lp, ILPDPCPMapper_2& vars);

		//Constraints
		//C1
		void constraint_1(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C2
		void constraint_2(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C3
		void constraint_3(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C4
		void constraint_4(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C5
		void constraint_5(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C6
		void constraint_6(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C7
		void constraint_7(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C8
		void constraint_8(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C9
		void constraint_9(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C10
		void constraint_10(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C11
		void constraint_11(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C12
		void constraint_12(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C13
		void constraint_13(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C14
		void constraint_14(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C15
		void constraint_15(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C16
		void constraint_16(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C17
		void constraint_17(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C18
		void constraint_18(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C19
		void constraint_19(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C20
		void constraint_20(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C21
		void constraint_21(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C22
		void constraint_22(LinearProgram& lp, ILPDPCPMapper_2& vars);
		//C23
		void constraint_23(LinearProgram& lp, ILPDPCPMapper_2& vars);

		bool alloc_schedulable();

	public:
		ILP_RTA_PFP_DPCP_2();
		ILP_RTA_PFP_DPCP_2(TaskSet tasks, ProcessorSet processors, ResourceSet resources);
		~ILP_RTA_PFP_DPCP_2();
		bool is_schedulable();
};

#endif































