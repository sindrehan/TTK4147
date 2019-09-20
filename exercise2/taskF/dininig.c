#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mtx1, mtx2, mtx3;


static inline void nonOptimizedBusyWait(void){
    for(long i = 0; i < 10000000; i++){
        // "Memory clobber" - tells the compiler optimizer that all the memory
        // is being touched, and that therefore the loop cannot be optimized out
        asm volatile("" ::: "memory");
    }
}



void* fnA(void* args){
    pthread_mutex_lock(&mtx1);
    printf("A pixked up 1\n");
    nonOptimizedBusyWait();
    pthread_mutex_lock(&mtx2);
    printf("A eats the rice\n");
    pthread_mutex_unlock(&mtx1);
    pthread_mutex_unlock(&mtx2);
    return NULL;
}

void* fnB(void* args){
    pthread_mutex_lock(&mtx3);
    printf("B picked up 2\n");
    nonOptimizedBusyWait();
    pthread_mutex_lock(&mtx2);
    printf("B eats the rice\n");
    pthread_mutex_unlock(&mtx2);
    pthread_mutex_unlock(&mtx3);
    return NULL;
}

void* fnC(void* args){
    pthread_mutex_lock(&mtx3);
    printf("C pixked up 3\n");
    nonOptimizedBusyWait();
    pthread_mutex_lock(&mtx1);
    printf("C eats the rice\n");
    pthread_mutex_unlock(&mtx1);
    pthread_mutex_unlock(&mtx3);
    return NULL;
}


int main(){
    pthread_mutex_t mtx1, mtx2, mtx3;


    // 2nd arg is a pthread_mutexattr_t
    pthread_mutex_init(&mtx1, NULL);
    pthread_mutex_init(&mtx2, NULL);
    pthread_mutex_init(&mtx3, NULL);


    pthread_t threadHandleA;
    pthread_create(&threadHandleA, NULL, fnA, "A");
    pthread_t threadHandleB;
    pthread_create(&threadHandleB, NULL, fnB, "B");
    pthread_t threadHandleC;
    pthread_create(&threadHandleC, NULL, fnC, "C");

    pthread_join(threadHandleA, NULL);
    pthread_join(threadHandleB, NULL);
    pthread_join(threadHandleC, NULL);

    printf("all philosophers are full\n");

    pthread_mutex_destroy(&mtx1);
    pthread_mutex_destroy(&mtx2);
    pthread_mutex_destroy(&mtx3);

}
