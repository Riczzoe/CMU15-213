#include "mylib.h"

void *thread(void *vargp);

volatile long cnt = 0;
sem_t mutex;            /* Semaphore that protects counter */

int main(int argc, char **argv) {
    long niters;
    pthread_t tid1, tid2;

    if (argc != 2) {
        printf("usage: %s <niters>\n", argv[0]);
        exit(0);
    }
    
    Sem_init(&mutex, 0, 1);
    niters = atoi(argv[1]);

    Pthread_create(&tid1, NULL, thread, &niters);
    Pthread_create(&tid2, NULL, thread, &niters);

    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    if (cnt != (2 * niters)) {
        printf("BOOM! cnt=%ld\n", cnt);
    } else {
        printf("OK cnt=%ld\n", cnt);
    }

    exit(0);
}

void *thread(void *vargp) {
    long i, niters = *((long *)vargp);

    for (i = 0; i < niters; i++) {
        sem_wait(&mutex);
        cnt++;
        sem_post(&mutex);
    }

    return NULL;
}
