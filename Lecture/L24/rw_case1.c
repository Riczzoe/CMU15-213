int readcnt = 0;
sem_t mutex, w;

void reader() {
    while (1) {
        P(&mutex);
        readcnt++;
        if (readcnt == 1)
            P(&w);
        V(&mutex);

        /* Reading */

        P(&mutex);
        readcnt--;
        if (readcnt == 0)
            V(&w);
        V(&mutex);
    }
}

void writer() {
    while (1) {
        P(&mutxe);
        /* Writting */
        V(&mutex);
    }
}
