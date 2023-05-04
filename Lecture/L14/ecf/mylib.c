/* 
 * mylib.c - Functions for csapp book
 */
#include    "mylib.h"

/* -----------------------------
 * | Error-handling fubnctions |
 * -----------------------------
 */

/* Unix-style error */
void unix_error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void posix_error(int code, char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

void gai_error(int code, char *msg) {
    fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
    exit(0);
}

void app_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(0);
}

/* -----------------------------------------------                                            
 * | Wrappers for Unix process control functions |
 * -----------------------------------------------
 */

pid_t Fork(void) {
    pid_t pid;
    if ((pid = fork()) < 0)
        unix_error("Fork error");
    return pid;
}

unsigned int snooze(unsigned int secs) {
    unsigned int rc = sleep(secs);
    printf("Slept for %d of %d secs.\n", secs-rc, secs);
    return rc;
}


/* ------------------------------------------
 * | Wrappers for the standard I/O functions |
 * ------------------------------------------
 */

char *Fgets(char *ptr, int n, FILE *stream) {
    char *rptr;
    if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream))
        app_error("Fgets error");
    return rptr;
}
