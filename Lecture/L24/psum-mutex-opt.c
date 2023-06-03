#include    "mylib.h"

#define MAXTHREADS 64

void *sum_array(void *vargp);

/* Global shared variables */
long gsum = 0;               /* Global sum */
long nelems_per_thread;     /* Number of elements to sum */
sem_t mutex;                /* and the mutex that protects it */
long psum[MAXTHREADS];      /* Local sums */

int main(int argc, char **argv) {
    long i, nelems, log_nelems, nthreads, myid[MAXTHREADS];
    pthread_t tid[MAXTHREADS];

    if (argc != 3) {
        fprintf(stderr, "usage: %s <nthreads> <log_nelems>\n", argv[0]);
        exit(0);
    }

    nthreads = atoi(argv[1]);
    log_nelems = atoi(argv[2]);
    nelems = (1L << log_nelems);
    nelems_per_thread = nelems / nthreads;
    sem_init(&mutex, 0, 1);

    for (i = 0; i < nthreads; i++) {
        myid[i] = i;
        Pthread_create(&tid[i], NULL, sum_array, &myid[i]);
    }
    
    for (i = 0; i < nthreads; i++) 
        Pthread_join(tid[i], NULL);

    for (i = 0; i < nthreads; i++) 
        gsum += psum[i];

    if (gsum != (nelems * (nelems - 1)) / 2)
        printf("Error: result = %ld\n", gsum);
    else
        printf("gsum = %ld\n", gsum);

    exit(0);
}

void *sum_array(void *vargp) {
    long myid = *((long *)vargp);
    long start = myid * nelems_per_thread;
    long end = start + nelems_per_thread;
    long i;
    psum[myid] = 0;

    for (i = start; i < end; i++) {
        psum[myid] += i;
    }
    return NULL;
}
