#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include "linked.h"
#include "__thread.h"
#include <signal.h>

void* 	__wrapperFunc(void* arg)
{
		void* ret;
		WrapperArg* pArg = (WrapperArg*)arg;
		sigset_t set;
		int retsig;
		//child sleeps until TCB is initialized
		sigemptyset(&set);
		sigaddset(&set, SIGUSR2);
		sigwait(&set, &retsig);
		//child is ready to run
		__thread_wait_handler(0);

		ret = (pArg->funcPtr)(&pArg->funcArg);

		return ret;
}


int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
		signal(SIGUSR1, __thread_wait_handler);
		Thread* tcb = init_link();

		WrapperArg wrapperArg;
		
		wrapperArg.funcPtr = start_routine;
		wrapperArg.funcArg = arg;
		
		pthread_create(thread, NULL, __wrapperFunc, &wrapperArg);
		
		tcb->status = THREAD_STATUS_READY;
		tcb->pExitCode = NULL;
		tcb->tid = *thread;
		tcb->readyCond = PTHREAD_COND_INITIALIZER;
		tcb->bRunnable = 0;
		tcb->readyMutex = PTHREAD_MUTEX_INITIALIZER;
		tcb->parentTid = thread_self();


		if(ReadyQHead == NULL && ReadyQTail == NULL){
			add_tcb_head(&ReadyQHead, &ReadyQTail, tcb );	
		}
		else {
			add_tcb(&ReadyQTail, tcb);
		}

		pthread_kill(tcb->tid, SIGUSR2);

		return 0;
}


int 	thread_join(thread_t thread, void **retval)
{

}


int 	thread_suspend(thread_t tid)
{

}


int	thread_resume(thread_t tid)
{

}

/*
int 		thread_cancel(thread_t tid)
{

}
*/

int thread_exit(void* retval)
{

}

thread_t	thread_self()
{
	return pthread_self();
}	
