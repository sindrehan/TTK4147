#include "array.h"
#include <stdio.h>

int main (void){
    Array a = array_new(2);
    for (int i = 0; i < 100; i++){
        array_insertBack(&a, 2);
        printf("%p -> %p\n", a.data, &a.data[a.capacity-1]);
    }
    array_print(a);
    array_destroy(a);
    return 0;
}
