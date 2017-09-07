#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define _BSD_SOURCE

int gVariable =0;

int main(){
    int lVariable=0;
    int i;

    pid_t pid = vfork();
    printf("\n");
    if(pid==0){
	for(i=0;i<10;i++){
	    gVariable++;
	    lVariable++;
	}
	printf("Child: local-%d global-%d",lVariable, gVariable);
	_exit(0);
    }
    else if( pid > 0){
	for(i=0;i<10;i++){
	    gVariable++;
	    lVariable++;
	}
	printf("Parent: local-%d global-%d",lVariable, gVariable);
    }
    else {
	printf("Fork failed");
    }
     printf("\n");
    return 0;
}
