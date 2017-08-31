#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <pthread.h>
#include <unistd.h>

#define PRINT_FUNCTION sleepy_print

void busy_wait_delay(int seconds)
{
    int i, dummy;
    int tps = sysconf(_SC_CLK_TCK);
    clock_t start;
    struct tms exec_time;
    times(&exec_time);
    start = exec_time.tms_utime;
    while( (exec_time.tms_utime - start) < (seconds * tps))
    {
	for(i=0; i<1000; i++)
	{
	    dummy = i;
	}
	times(&exec_time);
    }
}

void* sleepy_print(){
    printf("Hello\n");
    sleep(5);
    printf("Good bye!\n");
    return NULL;
}

void* busy_print(){
    printf("Hello\n");
    busy_wait_delay(5);
    printf("Good bye!\n");
    return NULL;
}

int main(){
    pthread_t thread_one;
    pthread_t thread_two;

    pthread_create(&thread_one, NULL, PRINT_FUNCTION, NULL);
    pthread_create(&thread_two, NULL, PRINT_FUNCTION, NULL);

    pthread_join(thread_one, NULL);
    pthread_join(thread_two, NULL);
    
    return 0;
}
