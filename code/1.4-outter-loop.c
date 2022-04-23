#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 590
#define CHUNKSIZE 10

int main(int argc, char *argv[]) {
    omp_set_num_threads(8);//set number of threads here
    int i, j, k, nthreads, tid, chunk;
    double sum;
    double start, end; // used for timing
    double A[N][N], B[N][N], C[N][N];
    
    chunk = CHUNKSIZE;


    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = j*1;
            B[i][j] = i*j+2;
            C[i][j] = j-i*2;
        }
    }
    
    start = omp_get_wtime(); //start time measurement
    for (i = 0; i < N; i++) 
    {
        #pragma omp parallel shared(A,B,C,nthreads,i) private(j,k,tid,sum) 
        {
            tid = omp_get_thread_num();
            if (tid == 0)
            {
                nthreads = omp_get_num_threads();
                //printf("Number of threads = %d\n", nthreads);
            }
            //printf("Thread %d starting...\n",tid);
            #pragma omp for schedule(dynamic,chunk)
            for (j = 0; j < N; j++) 
            {
                sum = 0;
                for (k=0; k < N; k++) 
                {
                    sum += A[i][k]*B[k][j];
                }
                C[i][j] = sum;
            }
        //printf("Thread %d done.\n",tid);
        }
    }

    end = omp_get_wtime(); //end time measurement
    printf("Time of computation: %f seconds\n", end-start);
    return(0);
}