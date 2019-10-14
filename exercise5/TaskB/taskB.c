#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include "io.h"

int set_cpu(int cpu_number){
	cpu_set_t cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_number, &cpu);

	return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu);
}

void* test_function(void * args){
    int channel = (int) args;
    printf("Channel nr: %d", channel);
    set_cpu(0);
    while(1){
        if (io_read(channel) == 0){
            io_write(channel, 0);
            usleep(5);
            io_write(channel, 1);
        }
    }
}

int main(void){
    io_init();
    pthread_t threadA, threadB, threadC;
    printf("Thread creation: %d", pthread_create(&threadA, NULL, &test_function, (void *) 1));
    printf("Thread creation: %d", pthread_create(&threadB, NULL, &test_function, (void *) 2));
    printf("Thread creation: %d", pthread_create(&threadC, NULL, &test_function, (void *) 3));
    
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
    return 0;
}