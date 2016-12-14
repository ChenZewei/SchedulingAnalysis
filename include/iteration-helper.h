#ifndef ITER_HELPER_H
#define ITER_HELPER_H

#define foreach_condition(tasks, condition) 		\
	for(uint i = 0; i < tasks.size(); i++)	\
	{					\
		if(condition)			\
			return false;		\
	}

#define foreach(collection, it)						\
	for (typeof(collection.begin()) it = (collection).begin();	\
	     it != (collection).end();					\
		     it++)

#define enumerate(collection, it, i)					\
	for (typeof(collection.begin()) it = ({i = 0; (collection).begin();}); \
	     it != (collection).end();					\
	     it++, i++)

#define apply_foreach(collection, fun, ...)				\
	foreach(collection, __apply_it_ ## collection) {		\
		fun(*__apply_it_ ## collection, ## __VA_ARGS__);	\
	}

#define map_ref(from, to, init, fun, ...)					\
	{								\
		(to).clear();						\
		(to).reserve((from).size());				\
		foreach(from, __map_ref_it) {				\
			(to).push_back(init());				\
			fun(*__map_ref_it, (to).back(),			\
			    ## __VA_ARGS__);				\
		}							\
	}

#define foreach_task_except(collection, ti, tx) \
	foreach(collection, tx)						\
		if(tx->get_id() != ti.get_id())

#define foreach_request_instance(task_ti, task_tx, request_index_variable)	\
	for(uint request_index_variable = 0, 												\
		max_request_num = ceiling((task_ti.get_response_time() + task_tx.get_response_time())/task_tx.get_period()); \
		request_index_variable < max_request_num; \
		request_index_variable++)

#define foreach_remote_request(task_ti, requests, request_iter) \
		foreach(requests, request_iter)	\
			if(task_ti.get_partition() != request_iter->get_locality())

#define foreach_local_request(task_ti, requests, request_iter) \
		foreach(requests, request_iter)	\
			if(task_ti.get_partition() == request_iter->get_locality())

#endif
