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

/* ----------------------------------------------                   
 * | Wrappers for Unix process control functions |
 * ----------------------------------------------
 */
void Execve(char *filename, char *const argv[], char *const envp[]) {
    if (execve(filename, argv, envp) < 0) 
        unix_error("Execve error");
    return;
}

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

void Kill(pid_t pid, int signum) {
    int rc;
    if ((rc = kill(pid, signum)) < 0)
        unix_error("Kill error");
}

void Pause() {
    (void)pause();
    return;
}

void Setpgid(pid_t pid, pid_t pgid) {
    int rc;

    if ((rc = setpgid(pid, pgid)) < 0)
        unix_error("Setpgid error");
    return;
}

unsigned int Sleep(unsigned int secs) {
    unsigned int rc;

    if ((rc = sleep(secs)) < 0)
        unix_error("Sleep error");
    return rc;
}

pid_t Getpgrp(void) {
    return getpgrp();
}

pid_t Waitpid(pid_t pid, int *statusp, int options) {
    pid_t rc;
    if ((rc = waitpid(pid, statusp, options)) < 0) 
        unix_error("Waitpid error");

    return rc;
}

/* -------------------------------------
 * | Wrappers for Unix signal functions |
 * -------------------------------------
 */
handler_t *Signal(int signum, handler_t *handler) {
    struct sigaction action, old_action;

    action.sa_handler = handler;    /* Set handler */
    sigemptyset(&action.sa_mask);   /* Empty mask */
    action.sa_flags = SA_RESTART;   /* Restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0)
        unix_error("Signal error");

    return (old_action.sa_handler);
}

void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
    if (sigprocmask(how, set, oldset) < 0)
        unix_error("Sigprocmask error");
    return;
}

void Sigemptyset(sigset_t *set) {
    if (sigemptyset(set) < 0) 
        unix_error("Sigemptyset error");
    return;
}

void Sigfillset(sigset_t *set) {
    if (sigfillset(set) < 0) 
        unix_error("Sigfillset error");
    return;
}

void Sigaddset(sigset_t *set, int signum) {
    if (sigaddset(set, signum) < 0)
        unix_error("Sigaddset error");
    return;
}

void Sigdelset(sigset_t *set, int signum) {
    if (sigdelset(set, signum) < 0)
        unix_error("Sigdelset error");
    return;
}

int Sigismember(const sigset_t *set, int signum) {
    int rc;
    if ((rc = sigismember(set, signum)) < 0)
        unix_error("Sigismember error");
    return rc;
}

/* --------------------------------------------------------------
 * | The sio (Signal-safe I/O) package - simple reentrant output |
 * | functions that are safe for signal handlers.                |
 * --------------------------------------------------------------
 */

/* Private sio functions */
/* sio_reverse - Reverse a string (from K&R) */
static void sio_reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* sio_ltoa - Convert long to base b string (from K&R) */
static void sio_ltoa(long v, char s[], int b) {
    int c, i = 0;
    int neg = v < 0;
    v = neg ? -v : v;
    
    do {
        s[i++] = (((c = (v % b)) < 10) ? c + '0' : c + 'a' - 10);
    } while ((v /= b) > 0);

    if (neg)
        s[i++] = '-';
    s[i] = '\0';
    sio_reverse(s);
}

static size_t sio_strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

/* Public sio functions */
ssize_t sio_puts(char s[]){
    return write(STDOUT_FILENO, s, strlen(s));
}

ssize_t sio_putl(long v) {
    char s[128];

    sio_ltoa(v, s, 10);
    return sio_puts(s);
}

void sio_error(char s[]) {
    sio_puts(s);
    _exit(1);
}

/* ---------------------------------
 * | Wrappers for the sio functions |
 * ---------------------------------
 */
ssize_t Sio_putl(long v) {
    ssize_t n;
    if ((n = sio_putl(v)) < 0)
        sio_error("Sio_putl error");
    return n;
}

ssize_t Sio_puts(char s[]) {
    ssize_t n;

    if ((n = sio_puts(s)) < 0) 
        sio_error("Sio_puts error");
    return n;
}

void Sio_error(char s[]) {
    sio_error(s);
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
