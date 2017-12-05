void __thread_wait_handler(int signo){
	Thread* pTh;

	pTh = find_tcb(ReadyQHead, thread_self());
	
	if(pTh == NULL){
		fprintf(stderr, "Error occured in thread_wait handler");
		exit(1);
	}

	pthread_mutex_lock( &(pTh->readyMutex) );
	while( pTh->bRunnable == 0 )
	{
		pthread_cond_wait( &(pTh->readyCond), &(pTh->readyMutex) );	
	}
	pthread_mutex_unlock( &(pTh->readyMutex) );
}

void __thread_wakeup(Thread* pTh)
{
	pthread_mutex_lock( &(pTh->readyMutex) );
	pTh->bRunnable = 1;
	pthread_cond_signal( &(pTh->readyCond) );
	pthread_mutex_unlock( &(pTh->readyMutex) );
}

