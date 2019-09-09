#include <assert.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <x86intrin.h>


int main() {
    const int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);

    for(int i = 0; i < 10*1000*1000; i++){
        int t1 = __rdtsc();
        int t2 = __rdtsc();

        int ns = (t2 - t1) * (1/1.992);

        if(ns >= 0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }
}


// Count tsc ticks in a second
// int main () {
//     int start = __rdtsc();
//     sleep(1);
//     int end = __rdtsc();
//     printf("%d", end-start);
// }
