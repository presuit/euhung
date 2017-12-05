#ifndef __LINKED_H__
#define __LINKED_H__
#include "Thread.h"
#include <stdio.h>
#include <stdlib.h>

Thread* init_link();
void add_tcb(Thread** tail_ptr, Thread* new_node);
void add_tcb_head(Thread** head_ptr, Thread** tail_ptr, Thread* new_node);
Thread* copy_head_tcb(Thread* node);
void remove_head_tcb(Thread** head_ptr);
void head_to_tail(Thread** head_ptr, Thread** tail_ptr);
Thread* find_tcb(Thread* head_ptr, thread_t tid);
void move_tcb(Thread* head_ptr, pthread_t tid, Thread** anothre_head_ptr);
void navigate_tcb(Thread* head_ptr);

#endif /* __LINKED_H__ */
