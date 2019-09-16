#include "array.h"
#include <stdio.h>
#include <malloc.h>

int main (void){
    Array a = array_new(10);
    for (int i = 0; i < 100; i++){
        array_insertBack(&a, 2);
    }
    array_print(a);
    array_destroy(a);
    return 0;
}
