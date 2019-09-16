#include "array.h"
#include <stdio.h>


int main (void){
    Array a = array_new(10);
    for (int i = 0; i < 12; i++){
        array_insertBack(&a, 2);
    }
    array_print(a);
    return 0;
}
