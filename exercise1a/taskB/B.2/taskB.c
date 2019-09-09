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
    struct tms buf;
    int ticks_per_second = sysconf(_SC_CLK_TCK);
    for(int i = 0; i < 10*1000*1000; i++){
        int t1 = times(&buf);
        int t2 = times(&buf);

        int ns = (t2 - t1) * 1000000000 / ticks_per_second;
        //printf("T1: %d\nT2: %d\nns: %ds\n", t1, t2, ns);
        if(ns >= 0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }
}
