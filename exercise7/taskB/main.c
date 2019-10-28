#include <stdio.h>
#include <native/task.h>
#include <native/timer.h>
#include <sys/mman.h>
#include <rtdk.h>
#include "io.h"
#include <pthread.h>
#include <native/sem.h>

RT_SEM g_sem_resource;
RT_SEM g_sem_sync;

#define TIME_UNIT_NS 10000

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
  rt_sem_p(&g_sem_resource, TM_INFINITE);
  rt_printf("Low working\n");
  busy_wait_us(TIME_UNIT_NS*3);
  rt_printf("Low done\n");
  rt_sem_v(&g_sem_resource);
}

void med_task_fun(void * args){
  rt_sem_p(&g_sem_sync, TM_INFINITE);
  rt_task_sleep(TIME_UNIT_NS);
  rt_printf("med working\n");
  busy_wait_us(5*TIME_UNIT_NS);
  rt_printf("med done\n");
}

void high_task_fun(void * args){
  rt_sem_p(&g_sem_sync, TM_INFINITE);
  rt_task_sleep(TIME_UNIT_NS*2);
  rt_sem_p(&g_sem_resource, TM_INFINITE);
  rt_printf("high working\n");
  busy_wait_us(TIME_UNIT_NS*2);
  rt_printf("high done\n");
  rt_sem_v(&g_sem_resource);
}


int main(void){
  mlockall(MCL_CURRENT | MCL_FUTURE);
  rt_task_shadow(NULL, "main_task", 0, T_CPU(0));
  rt_print_auto_init(1);
  rt_sem_create(&g_sem_resource, "g_sem_resource", 1, S_PRIO);
  rt_sem_create(&g_sem_sync, "g_sem_sync", 0, S_PRIO);

  RT_TASK low_task, med_task, high_task;
  rt_task_create(&low_task, "low", 0, 97, T_CPU(0));
  rt_task_create(&med_task, "medium", 0, 98, T_CPU(0));  
  rt_task_create(&high_task, "high", 0, 99, T_CPU(0));

  rt_task_start(&low_task, &low_task_fun, (void *) 1);
  rt_task_start(&med_task, &med_task_fun, (void *) 2);
  rt_task_start(&high_task, &high_task_fun, (void *) 3);
  
  rt_sem_broadcast(&g_sem_sync);
  rt_sem_delete(&g_sem_resource);
  rt_sem_delete(&g_sem_sync);
  return 0;
}
