#ifndef     MYLIB_H
#define     MYLIB_H

#include    <stdio.h>
#include    <errno.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include    <netdb.h>
#include    <sys/types.h>
#include    <sys/wait.h>

/* External variables */
extern char **environ;     /* Defined in libc */

/* Misc constants */
#define MAXLINE    8192    /* Max text line length */
#define MAXBUF     8192    /* Max I/O buffer size */

/* Our own error-handling functions */
void unix_error(char *msg);
void posix_error(int code, char *msg);
void gai_error(int code, char *msg);
void app_error(char *msg);


/* Process control wrappers */
pid_t Fork(void);
unsigned int snooze(unsigned int secs);


/* Standard I/O wrappers */
char *Fgets(char *ptr, int n, FILE *stream);

#endif // MYLIB_H
