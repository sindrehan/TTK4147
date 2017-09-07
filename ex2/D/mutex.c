#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int running = 1;
int var1 = 0;
int var2 = 0;
pthread_mutex_t mutex; 

void *thread1(){
    while(running) {
	pthread_mutex_lock(&mutex);
	var1++;
	var2 = var1;
	pthread_mutex_unlock(&mutex);
    }
}

void *thread2(){
    for (int i = 0; i < 20; i++){
	pthread_mutex_lock(&mutex);
	printf("Number 1 is %d, number 2 is %d\n", var1, var2);
	pthread_mutex_unlock(&mutex);
	usleep(100000);
    }
    running = 0;
}

int main(){
    pthread_t thread1_id, thread2_id;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread1_id, NULL, thread1, NULL);
    pthread_create(&thread2_id, NULL, thread2, NULL);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    return 0;
}
