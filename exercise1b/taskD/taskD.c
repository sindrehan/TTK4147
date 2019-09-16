#include <stdio.h>
#include <stdlib.h>

int main(void) {
    long xy_size    = 1000*1000*1000*2;       // 8 GB (sizeof(long) = 8 bytes)
    long x_dim      = 10000;
    long y_dim      = xy_size/x_dim;

    long** matrix   = malloc(y_dim*sizeof(long*));

    for(long y = 0; y < y_dim; y++){
        matrix[y] = malloc(x_dim*sizeof(long));
        memset(matrix[y], 10, x_dim*sizeof(long));
    }

    printf("Allocation complete (press any key to continue...)\n");
    getchar();
    return 0;
}
