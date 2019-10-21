#include <stdio.h>
#include <native/task.h>
#include <native/timer.h>
#include <sys/mman.h>
#include <rtdk.h>


void print_hello(){
  rt_task_set_periodic(NULL, TM_NOW, 1000000000);
  while(1){
    rt_task_wait_period(NULL);
    printf("Helloo\n");
  }
}

int main(void){
  //rt_print_auto_init(1);
  mlockall(MCL_CURRENT | MCL_FUTURE);
  
  RT_TASK print_task;
  int err = rt_task_create(&print_task, "print_task", 0, 0, T_CPU(0));
  if(!err){
    rt_task_start(&print_task, &print_hello, NULL);

  }else{
    printf("many fuck");
  }
  
  while(1){};
  rt_task_delete(&print_task);
  return 0;
}
