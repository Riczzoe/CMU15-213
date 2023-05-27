#include "mylib.h"

void *thread1(void *vargp) {
    printf("Hello, world! from thread1.\n");
    pthread_t tid2;
    tid2 = Pthread_self();
    printf("tid in thread1: %d\n", (int)tid2);
    return NULL;
}

void *thread2(void *vargp) {
    /* set cancel type to asynchronous, so thread2 can be canceled at any time. */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    printf("cancel myself, so thread2 will not print hello world.\n");
    pthread_cancel(pthread_self());
    printf("Hello, world! from thread2.\n");
    return NULL;
}

void *thread3(void *vargp) {
    printf("Call pthread_exit, so thread3 will not print hello world.\n");
    pthread_exit(NULL);
    printf("Hello, world! from thread3.\n");
    return NULL;
}

void *thread4(void *vargp) {
    printf("Call exit, so thread4 will not print hello world." \
            "And the main thread will not print hello world.\n");
    exit(0);
    printf("Hello, world! from thread4.\n");
    return NULL;
}


int main() {
    pthread_t tid1, tid2, tid3, tid4;
    Pthread_create(&tid1, NULL, thread1, NULL);
    Pthread_join(tid1, NULL);
    Pthread_create(&tid2, NULL, thread2, NULL);
    Pthread_join(tid2, NULL);
    Pthread_create(&tid3, NULL, thread3, NULL);
    Pthread_join(tid3, NULL);
    Pthread_create(&tid4, NULL, thread4, NULL);

    printf("Hello, world! from main thread.\n");
    while (1) {
        printf("main thread is running.\n");
        Sleep(1);
    }
}
