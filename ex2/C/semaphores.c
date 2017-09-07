#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t sem_resource;

int use_resource(){
    for (int i = 1; i <= 4; i++){
	printf("Thread number:  %d\n", i);
	usleep(100000);
    }
    return 0;
}

void *resource_thread(){
    sem_wait(&sem_resource);
    use_resource();
    sem_post(&sem_resource);
}

int main(){
    pthread_t tid[5];
    sem_init(&sem_resource, 0, 3);
    for (int i = 0; i < 5; i++) {
	pthread_create(&tid[i], NULL, resource_thread, NULL);
    }

    for (int i = 0; i < 5; i++) {
	pthread_join(tid[i], NULL);
    }
    
    return 0;
}
