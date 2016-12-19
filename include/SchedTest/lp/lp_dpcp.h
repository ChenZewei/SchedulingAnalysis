#ifndef LP_DPCP_H
#define LP_DPCP_H

class Task;
class TaskSet;
class Resource;
class ResourceSet;
class ProcessorSet;
class VarMapper;
class LinearProgram;


void lp_dpcp_local_objective(const Task& ti, const TaskSet& tasks, const ResourceSet& resources, LinearProgram& lp, VarMapper& vars);

void lp_dpcp_remote_objective(const Task& ti, const TaskSet& tasks, const ResourceSet& resources, LinearProgram& lp, VarMapper& vars);

//Constraint 1 [BrandenBurg 2013 RTAS] Xd(x,q,v) + Xi(x,q,v) + Xp(x,q,v) <= 1
void lp_dpcp_constraint_1(const Task& ti, const TaskSet& tasks, const ResourceSet& resources, LinearProgram& lp, VarMapper& vars);

//Constraint 2 [BrandenBurg 2013 RTAS] for any remote resource lq and task tx except ti Xp(x,q,v) = 0
void lp_dpcp_constraint_2(const Task& ti, const TaskSet& tasks, const ResourceSet& resources, LinearProgram& lp, VarMapper& vars);

//Constraint 3 [BrandenBurg 2013 RTAS]
void lp_dpcp_constraint_3(const Task& ti, const TaskSet& tasks, const ResourceSet& resources, LinearProgram& lp, VarMapper& vars);


#endif
