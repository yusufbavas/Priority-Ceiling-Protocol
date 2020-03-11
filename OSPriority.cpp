#include "OSPriority.hpp"

#ifdef LINUX
	#include <pthread.h>
#endif

#include <iostream>

int OSPriority::getPriority(){

	#ifdef LINUX
		int policy;
	    struct sched_param param;

		pthread_getschedparam(pthread_self(), &policy, &param);

		/*if (policy != SCHED_RR){

			policy = SCHED_RR;
			pthread_setschedparam(pthread_self(), policy,&param);
			pthread_getschedparam(pthread_self(), &policy, &param);
		}*/
		return param.sched_priority;
	#endif
	
}

void OSPriority::setPriority(int priority){

	#ifdef LINUX
		struct sched_param param;

	    param.sched_priority = priority;
	    pthread_setschedparam(pthread_self(), SCHED_RR, &param);
	#endif
}