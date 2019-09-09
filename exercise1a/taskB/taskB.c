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


int rdtsc() {
    for (int i = 0; i < 10*1000*1000; i++){
        __rdtsc();
    }
}

int gettime() {
    struct timespec now;
    for (int i = 0; i < 10*1000*1000; i++){
        clock_gettime(CLOCK_MONOTONIC, &now);
    }
}

int tiimes() {
    struct tms buf;
    for(int i = 0; i < 10*1000*1000; i++){
        times(&buf);
    }
}

int main() {
    //rdtsc(); // 0.122s
    //gettime(); // 0.287s
    tiimes(); // 4.002s
    return 0;
}
