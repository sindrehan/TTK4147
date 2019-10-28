#include <stdio.h>
#include <native/task.h>
#include <native/timer.h>
#include <sys/mman.h>
#include <rtdk.h>
#include "io.h"
#include <pthread.h>
#include <native/sem.h>

RT_SEM g_semaphore;

int set_cpu(int cpu_number){
	cpu_set_t cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_number, &cpu);

	return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu);
}

void print_task(void * args){
  int task_num = (int) args;
  rt_sem_p(&g_semaphore, TM_INFINITE);
  rt_printf("Hello from %d\n", task_num);
}

int main(void){
  mlockall(MCL_CURRENT | MCL_FUTURE);
  rt_task_shadow(NULL, "main_task", 0, T_CPU(0));
  rt_print_auto_init(1);
  rt_sem_create(&g_semaphore, "g_semaphore", 0, S_PRIO);

  RT_TASK print_task_a, print_task_b;
  rt_task_create(&print_task_a, "print_task_a", 0, 0, T_CPU(0));
  rt_task_create(&print_task_b, "print_task_b", 0, 0, T_CPU(0));
  rt_task_start(&print_task_a, &print_task, (void *) 1);
  rt_task_start(&print_task_b, &print_task, (void *) 2);
  rt_timer_spin(100000);
  rt_sem_broadcast(&g_semaphore);
  rt_timer_spin(100000);
  rt_sem_delete(&g_semaphore);
  return 0;
}
