#ifndef     SBUF_H
#define     SBUF_H

#include    "mylib.h"

typedef struct {
    int *buf;       /* Buffer array */
    int n;          /* Max number of slots */
    int front;      /* The first item: buf[(front + 1) % n] */
    int rear;       /* The last item: buf[rear % n] */
    sem_t mutex;    /* Protect to access buf */
    sem_t slots;    /* Counts of avildable slots */
    sem_t items;    /* Counts of avildable items */
} sbuf_t;


/* Function prototypes */

/** sbuf_init - Initialize a shared buffer */
void sbuf_init(sbuf_t *sbuf, int n);

/** sbuf_deinit - Deinitialize a shared buffer */
void sbuf_deinit(sbuf_t *sbuf);

/** sbuf_insert - Insert an item to the shared buffer */
void sbuf_insert(sbuf_t *sbuf, int item);

/** sbuf_remove - Remove an item from the shared buffer */
int sbuf_remove(sbuf_t *sbuf);

#endif  // SBUF_H
