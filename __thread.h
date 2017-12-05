#include "thread.h"
#include "linked.h"

void __thread_wait_handler(int signo);
void __thread_wakeup(Thread* pTh);
