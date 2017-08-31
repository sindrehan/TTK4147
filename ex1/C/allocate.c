#include <stdlib.h>
#include <stdio.h>

void allocate(int value){
    int *ptr = NULL;
    ptr = malloc(1024*1024*sizeof(char));
    if (ptr != NULL){
	*ptr = value;
	printf("test of allocated memory: %i\n", *ptr);
    } else {
	perror("Error: ");
	exit(0);
    }
}

int main(){
    while (1){
	allocate(1);
    }
}
