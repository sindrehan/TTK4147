#define _GNU_SOURCE
#include <pthread.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include "io.h"
#include <stdio.h>

int set_cpu(int cpu_number){
	cpu_set_t cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_number, &cpu);

	return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu);
}

struct timespec timespec_normalized(time_t sec, long nsec){
    while(nsec >= 1000000000){
        nsec -= 1000000000;
        ++sec;
    }
    while(nsec < 0){
        nsec += 1000000000;
        --sec;
    }
    return (struct timespec){sec, nsec};
}

struct timespec timespec_add(struct timespec lhs, struct timespec rhs){
    return timespec_normalized(lhs.tv_sec + rhs.tv_sec, lhs.tv_nsec + rhs.tv_nsec);
}

void* test_function(void * args){
    set_cpu(0);
    int channel = (int) args;
    printf("Channel nr: %d\n", channel);
    struct timespec waketime;
    clock_gettime(CLOCK_REALTIME, &waketime);

    struct timespec period = {.tv_sec = 0, .tv_nsec = 1000*1000};
    while(1){
        if (io_read(channel) == 0){
            io_write(channel, 0);
            usleep(5);
            io_write(channel, 1);
        }
        waketime = timespec_add(waketime, period);
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &waketime, NULL);
    }
}



void* reg_print(void * args){
    struct timespec waketime;
    clock_gettime(CLOCK_REALTIME, &waketime);

    struct timespec period = {.tv_sec = 0, .tv_nsec = 500*1000*1000};

    while(1){
        printf("hallo\n");
        waketime = timespec_add(waketime, period);
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &waketime, NULL);
    }
}

void* disturbance(void * args){
    set_cpu(0);
    while (1){
        asm volatile("" ::: "memory");
        usleep(5);
    }
}

int main(void){
    io_init();
    pthread_t threadA, threadB, threadC;
    printf("Thread creation: %d\n", pthread_create(&threadA, NULL, &test_function, (void *) 1));
    printf("Thread creation: %d\n", pthread_create(&threadB, NULL, &test_function, (void *) 2));
    printf("Thread creation: %d\n", pthread_create(&threadC, NULL, &test_function, (void *) 3));
    pthread_t d0, d1, d2, d3, d4, d5, d6, d7, d8, d9;
    pthread_create(&d0, NULL, &disturbance, NULL);
    pthread_create(&d1, NULL, &disturbance, NULL);
    pthread_create(&d2, NULL, &disturbance, NULL);
    pthread_create(&d3, NULL, &disturbance, NULL);
    pthread_create(&d4, NULL, &disturbance, NULL);
    pthread_create(&d5, NULL, &disturbance, NULL);
    pthread_create(&d6, NULL, &disturbance, NULL);
    pthread_create(&d7, NULL, &disturbance, NULL);
    pthread_create(&d8, NULL, &disturbance, NULL);
    pthread_create(&d9, NULL, &disturbance, NULL);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
    return 0;
} 