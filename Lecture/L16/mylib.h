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
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <dirent.h>

/* Default file permissions are DEF_MODE & ~DEF_UMASK   */
#define     DEF_MODE    S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
#define     DEF_UMASK   S_IWGRP|S_IWOTH

/* Persistent state for the robust I/O (RIO) package    */
/* $begin rio_t */
#define     RIO_BUFSIZE 8192
typedef struct {
    int rio_fd;                 /* Descriptor for this internal buf */
    int rio_cnt;                /* Unread bytes in internal buf */
    char *rio_bufptr;           /* Next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE];  /* Internal buf */
} rio_t;
/* $end rio_t   */

/* External variables */
extern char **environ;     /* Defined in libc */

/* Misc constants */
#define     MAXLINE    8192    /* Max text line length */
#define     MAXBUF     8192    /* Max I/O buffer size */

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

/* Unix I/O wrappers */
int Open(const char *pathname, int flags, mode_t mode);
ssize_t Read(int fd, void *buf, size_t count);
ssize_t Write(int fd, const void *buf, size_t count);
off_t Lseek(int fildes, off_t offset, int whence);
void Close(int fd);
int Select(int  n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, 
               struct timeval *timeout);
int Dup2(int fd1, int fd2);
void Stat(const char *filename, struct stat *buf);
void Fstat(int fd, struct stat *buf) ;

/* Standard I/O wrappers */
char *Fgets(char *ptr, int n, FILE *stream);

/* Rio (Robust I/O) package */
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

#endif // MYLIB_H
