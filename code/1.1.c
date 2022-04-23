#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int nthreads, tid;

    // Fork a team of threads with their own copies of variables
    omp_set_num_threads(32);
    #pragma omp parallel private(nthreads, tid)
    {
        tid = omp_get_thread_num(); // Obtain thread number
        printf("Hello World from thread = %d\n", tid);

        if (tid == 0) { // Only master thread does this
            nthreads = omp_get_num_threads();
        printf("Number of threads = %d\n", nthreads);
        }
    } // All threads join master thread and disband
    return(0);
}