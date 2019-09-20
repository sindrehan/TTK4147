#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

long my_global = 0;
sem_t global_sem;

// Note the argument and return types: void*
void* fnA(void* args){
    long my_local = 0;

    for(int i = 0; i<500000; i++){
        my_local++;
        sem_wait(&global_sem);
        my_global++;
        sem_post(&global_sem);
    }
    printf("Local in A is: %ld \n", my_local);
    return NULL;
}

void* fnB(void* args){
    long my_local = 0;

    for(int i = 0; i<500000; i++){
        my_local++;
        sem_wait(&global_sem);
        my_global++;
        sem_post(&global_sem);
    }
    printf("Local in B is: %ld \n", my_local);
        return NULL;
}

int main(){
    sem_init(&global_sem, 0, 1);


    pthread_t threadHandleA;
    pthread_create(&threadHandleA, NULL, fnA, "A");
    pthread_t threadHandleB;
    pthread_create(&threadHandleB, NULL, fnB, "B");

    pthread_join(threadHandleA, NULL);
    pthread_join(threadHandleB, NULL);

    printf("My global : %ld \n", my_global);

}
