#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_OF_PHILOSOPHERS 5

int plates_left = NUMBER_OF_PHILOSOPHERS;
pthread_mutex_t forks[NUMBER_OF_PHILOSOPHERS];
pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];

void* philosopher(void *number){
    int done = 0;
    int phil_num = (int)number;
    int left_fork = phil_num;
    int right_fork = phil_num + 1;
    if (phil_num == NUMBER_OF_PHILOSOPHERS - 1){
        right_fork = 0;
    }

    while (!done) {
	usleep(10000*(rand()%10));
	pthread_mutex_lock(&forks[left_fork]);
	printf("Philosopher %d got left fork\n", phil_num);
	
	pthread_mutex_lock(&forks[right_fork]);
	printf("Philosopher %d got right fork and is eating\n", phil_num);
	usleep(100000);
	printf("Philosopher %d is done eating\n", phil_num);
	pthread_mutex_unlock(&forks[right_fork]);
	printf("Philosopher %d released right fork\n", phil_num);
	pthread_mutex_unlock(&forks[left_fork]);
	printf("Philosopher %d released left fork\n", phil_num);
	done = 1;
    }
    plates_left--;
    printf("Plates left: %d\n", plates_left);
    return NULL;
}

int main(){   
    for (int i = 0; i<NUMBER_OF_PHILOSOPHERS; i++){
	pthread_mutex_init(&forks[i], NULL);
	pthread_create(&philosophers[i], NULL, philosopher, (void *)i);
    }

    while(plates_left > 0){
    }
    for (int i = 0; i<NUMBER_OF_PHILOSOPHERS; i++){
	pthread_join(philosophers[i], NULL);
    }
    return 0;
}
