#include <stdio.h>
#include <native/task.h>
#include <native/timer.h>
#include <sys/mman.h>
#include <rtdk.h>
#include "io.h"
#include <pthread.h>
#include <native/sem.h>
#include <native/mutex.h>

RT_MUTEX g_mutex_a;
RT_MUTEX g_mutex_b;
RT_SEM g_sem_sync;

#define TIME_UNIT 100000

int set_cpu(int cpu_number){
	cpu_set_t cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_number, &cpu);

	return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu);
}

void busy_wait_us(unsigned long delay){
  for(; delay > 0; delay--){
    rt_timer_spin(1000);
  }
}

void low_task_fun(void * args){
  rt_sem_p(&g_sem_sync, TM_INFINITE);
  rt_mutex_acquire(&g_mutex_a, TM_INFINITE);
  rt_printf("Low working with A\n");
  busy_wait_us(TIME_UNIT*3);
  rt_mutex_acquire(&g_mutex_b, TM_INFINITE);
  rt_printf("Low working with B\n");
  busy_wait_us(TIME_UNIT*3);
  rt_mutex_release(&g_mutex_b);
  rt_printf("Low done with B\n");
  rt_mutex_release(&g_mutex_a);
  rt_printf("Low done with A\n");
}

void high_task_fun(void * args){
  rt_sem_p(&g_sem_sync, TM_INFINITE);
  rt_task_sleep(TIME_UNIT*1000);
  rt_mutex_acquire(&g_mutex_b, TM_INFINITE);
  rt_printf("High working with B\n");
  busy_wait_us(TIME_UNIT*1);
  rt_mutex_acquire(&g_mutex_a, TM_INFINITE);
  rt_printf("High working with A\n");
  busy_wait_us(TIME_UNIT*2);
  rt_mutex_release(&g_mutex_a);
  rt_printf("High done with A\n");
  rt_mutex_release(&g_mutex_b);
  rt_printf("High done with B\n");
}


int main(void){
  mlockall(MCL_CURRENT | MCL_FUTURE);
  rt_task_shadow(NULL, "main_task", 0, T_CPU(0));
  rt_print_auto_init(1);
  rt_mutex_create(&g_mutex_a, "mutex_a");
  rt_mutex_create(&g_mutex_b, "mutex_b");
  rt_sem_create(&g_sem_sync, "g_sem_sync", 0, S_PRIO);

  RT_TASK low_task, high_task;
  rt_task_create(&low_task, "low", 0, 1, T_CPU(0));
  rt_task_create(&high_task, "high", 0, 2, T_CPU(0));

  rt_task_start(&low_task, &low_task_fun, (void *) 1);
  rt_task_start(&high_task, &high_task_fun, (void *) 3);
  
  rt_sem_broadcast(&g_sem_sync);
  rt_task_join(&low_task);
  rt_task_join(&high_task);
  rt_mutex_delete(&g_mutex_a);
  rt_mutex_delete(&g_mutex_b);
  rt_sem_delete(&g_sem_sync);
  return 0;
}
