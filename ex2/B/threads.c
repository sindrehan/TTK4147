#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int gVariable=0;
int nThread=1;

void *myThread(){
    int lVariable=0;
    int numThread=nThread;
    nThread++;
    for(int i=0;i<10;i++){
	gVariable++;
	lVariable++;
    }
    printf("Thread %d: local-%d global-%d", numThread, lVariable, gVariable);
    printf("\n");
}

int main(){
    pthread_t tid[2];
    int i;
    printf("We are going to create 2 threads \n\n");
    for(i=0;i<2;i++){
	pthread_create(&tid[i], NULL, myThread, NULL);
    }

    for(i=0;i<2;i++){
	pthread_join(tid[i], NULL);
    }
    printf("\n");
    return 0;
}
