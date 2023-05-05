#ifndef     MYLIB_H
#define     MYLIB_H

#include    <stdio.h>
#include    <errno.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include    <netdb.h>
#include    <setjmp.h>
// #include    <signal.h>
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
void Execve(char *filename, char *const argv[], char *const envp[]);
pid_t Fork(void);
unsigned int snooze(unsigned int secs);
void Kill(pid_t pid, int signum);
void Pause(void);
unsigned int Sleep(unsigned int secs);
void Setpgid(pid_t pid, pid_t pgid);
pid_t Waitpid(pid_t pid, int *statusp, int options);
pid_t Getpgrp(void);


/* Signal wrappers */
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);
void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
void Sigemptyset(sigset_t *set);
void Sigfillset(sigset_t *set);
void Sigaddset(sigset_t *set, int signum);
void Sigdelset(sigset_t *set, int signum);
int Sigismember(const sigset_t *set, int signum);

/* Standard I/O wrappers */
char *Fgets(char *ptr, int n, FILE *stream);

#endif // MYLIB_H
