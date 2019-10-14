#define _GNU_SOURCE
#include <pthread.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include "io.h"
#include <stdio.h>

void* test_function(void * args){
    int channel = (int) args;
    printf("Channel nr: %d\n", channel);
    while(1){
        //int val = io_read(channel);
        //printf("Channel %d: %d\n", channel, val);
        if (io_read(channel) == 0){
            io_write(channel, 0);
            usleep(5);
            io_write(channel, 1);
        }
    }
}

int main(void){
    printf("hei\n");
    io_init();
    pthread_t threadA, threadB, threadC;
    printf("Thread creation: %d\n", pthread_create(&threadA, NULL, &test_function, (void *) 1));
    printf("Thread creation: %d\n", pthread_create(&threadB, NULL, &test_function, (void *) 2));
    printf("Thread creation: %d\n", pthread_create(&threadC, NULL, &test_function, (void *) 3));

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
    return 0;
}