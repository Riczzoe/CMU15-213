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
pid_t Wait(int *status) {
    pid_t pid;

    if ((pid = wait(status)) < 0)
        unix_error("Wait error");
    return pid;
}

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


/* -----------------------------------
 * | Wrappers for Unix I/O functions  |
 * -----------------------------------
 */

int Open(const char *pathname, int flags, mode_t mode) {
    int rc;

    if ((rc = open(pathname, flags, mode))  < 0)
        unix_error("Open error");
    return rc;
}

ssize_t Read(int fd, void *buf, size_t count) {
    ssize_t rc;

    if ((rc = read(fd, buf, count)) < 0) 
        unix_error("Read error");
    return rc;
}

ssize_t Write(int fd, const void *buf, size_t count) {
    ssize_t rc;

    if ((rc = write(fd, buf, count)) < 0)
        unix_error("Write error");
    return rc;
}

off_t Lseek(int fildes, off_t offset, int whence) {
    off_t rc;

    if ((rc = lseek(fildes, offset, whence)) < 0)
        unix_error("Lseek error");
    return rc;
}

void Close(int fd) {
    int rc;

    if ((rc = close(fd)) < 0)
        unix_error("Close error");
}

int Select(int  n, fd_set *readfds, fd_set *writefds,
        fd_set *exceptfds, struct timeval *timeout) {
    int rc;

    if ((rc = select(n, readfds, writefds, exceptfds, timeout)) < 0)
        unix_error("Select error");
    return rc;
}

int Dup2(int fd1, int fd2) {
    int rc;

    if ((rc = dup2(fd1, fd2)) < 0)
        unix_error("Dup2 error");
    return rc;
}

void Stat(const char *filename, struct stat *buf) {
    if (stat(filename, buf) < 0)
        unix_error("Stat error");
}

void Fstat(int fd, struct stat *buf) {
    if (fstat(fd, buf) < 0)
        unix_error("Fstat error");
}

/* ----------------------------------
 * | Wrappers for directory function |
 * ----------------------------------
 */
DIR *Opendir(const char *name) {
    DIR *dirp = opendir(name);

    if (!dirp)
        unix_error("opendir error");
    return dirp;
}

struct dirent *Readdir(DIR *dirp) {
    struct dirent *dep;

    errno = 0;
    dep = readdir(dirp);
    if ((dep == NULL) && (errno != 0)) 
        unix_error("readdir error");
    return dep;
}

int Closedir(DIR *dirp) {
    int rc;

    if ((rc = closedir(dirp)) < 0)
        unix_error("closedir error");
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

/* ----------------------------------------
 * | Wrappers for the memory map functions |
 * ---------------------------------------
 */
void *Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset) {
    void *ptr;
    
    if ((ptr = mmap(addr, len, prot, flags, fd, offset)) == (void *) -1)
        unix_error("mmap error");

    return ptr;
}

void *Munmap(void *start, size_t len) {
    if (Munmap(start, len) < 0) 
        unix_error("munmap error");
}
/* -------------------------------------------------------
 * | Wrappers for the Dynamic storge allocating functions |
 * -------------------------------------------------------
 */
void *Malloc(size_t size) {
    void *p;

    if ((p = malloc(size)) == NULL) 
        unix_error("Malloc errir");
    return p;
}

void *Realloc(void *ptr, size_t size) {
    void *p;

    if ((p = realloc(ptr, size)) == NULL) 
        unix_error("Realloc error");
    return p;
}

void *Calloc(size_t nmemb, size_t size) {
    void *p;

    if ((p = calloc(nmemb, size)) == NULL)
        unix_error("Calloc error");
    return p;
}

void Free(void *ptr) {
    free(ptr);
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

/* -------------------------------------------
 * | Wrappers for the standard I/O functions. |
 * -------------------------------------------
 */
int Socket(int domain, int type, int protocol) {
    int rc;

    if ((rc = socket(domain, type, protocol)) < 0)
        unix_error("Socket error");
    return rc;
}

void Setsockopt(int s, int level, int optname, const void *optval, int optlen) 
{
    int rc;

    if ((rc = setsockopt(s, level, optname, optval, optlen)) < 0)
        unix_error("Setsockopt error");
}

void Bind(int sockfd, struct sockaddr *my_addr, int addrlen) 
{
    int rc;

    if ((rc = bind(sockfd, my_addr, addrlen)) < 0)
        unix_error("Bind error");
}

void Listen(int s, int backlog) 
{
    int rc;

    if ((rc = listen(s,  backlog)) < 0)
        unix_error("Listen error");
}

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen) 
{
    int rc;

    if ((rc = accept(s, addr, addrlen)) < 0)
        unix_error("Accept error");
    return rc;
}

void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen) 
{
    int rc;

    if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
        unix_error("Connect error");
}

/* --------------------------------
 * | Protocol-independent wrappers |
 * --------------------------------
 */

/* $begin getaddrinfo */
void Getaddrinfo(const char *node, const char *service, 
        const struct addrinfo *hints, struct addrinfo **res)
{
    int rc;

    if ((rc = getaddrinfo(node, service, hints, res)) != 0) 
        gai_error(rc, "Getaddrinfo error");
}
/* $end getaddrinfo */

void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, 
        size_t hostlen, char *serv, size_t servlen, int flags)
{
    int rc;

    if ((rc = getnameinfo(sa, salen, host, hostlen, serv, 
                    servlen, flags)) != 0) 
        gai_error(rc, "Getnameinfo error");
}

void Freeaddrinfo(struct addrinfo *res)
{
    freeaddrinfo(res);
}

void Inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
    if (!inet_ntop(af, src, dst, size))
        unix_error("Inet_ntop error");
}

void Inet_pton(int af, const char *src, void *dst) 
{
    int rc;

    rc = inet_pton(af, src, dst);
    if (rc == 0)
        app_error("inet_pton error: invalid dotted-decimal address");
    else if (rc < 0)
        unix_error("Inet_pton error");
}

/* -----------------------------------------
 * | The Rio package - robust I/O functions |
 * -----------------------------------------
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char *buf = usrbuf;

    while (nleft > 0) {
        if ((nread = read(fd, usrbuf, nleft)) < 0) {
            if (errno == EINTR)     /* Interrupted by sig handler return */
                nread = 0;          /* and call read() again */
            else
                return -1;          /* errno set by read() */
        }

        if (nread == 0)
            break;

        nleft -= nread;
        buf += nread;
    }

    return n - nleft;
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    char *buf = usrbuf;

    while (nleft > 0) {
        if ((nwritten = write(fd, buf, nleft)) < 0) {
            if (errno = EINTR)
                nwritten = 0;
            else
                return -1;
        }

        nleft -= nwritten;
        buf += nwritten;
    }

    return n;
}


void rio_readinitb(rio_t *rp, int fd) {
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

/* rio_read - This is a wrapper for the Unix read(0 function that
 *   transfers min(n, rio_cnt) bytes from an internal buffer to a user
 *   buffer, wherr n is the number of bytes requested by the user and
 *   rio_cnt is the number of unread bytes in the internal buffer. On 
 *   entry, rio_read() refills the internal buffer via a call to 
 *   read() if the internal buffer is empty.
 */
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n) {
    int cnt;

    while (rp->rio_cnt <= 0) {   /* If buf is empty, fill it */
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, 
                sizeof(rp->rio_buf));

        if (rp->rio_cnt < 0) {
            if (errno != EINTR) /* Interrupted bu sig handler return */
                return -1;
        } else if (rp->rio_cnt == 0)    /* EFO  */
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf;   /* If refill success, reset buffer ptr */
    }

    cnt = n;
    if (rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);

    /* Update rp */
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) {
    int n, rc;
    char c, *buf = usrbuf;

    for (n = 1; n < maxlen; n++) {
        if ((rc = rio_read(rp, &c, 1)) == 1) {
            *buf++ = c;
            if (c == '\n') {
                n++;
                break;
            }
        } else if (rc == 0) {
            if (n == 1) 
                return 0;
            else 
                break;
        } else 
            return -1;
    }

    *buf = 0;
    return n - 1;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char *buf = usrbuf;

    while (nleft > 0) {
        if ((nread = rio_read(rp, buf, nleft)) < 0) 
            return -1;
        else if (nread == 0)
            break;
        
        nleft -= nread;
        buf += nread;
    }

    return n - nleft;
}


/* ------------------------------------
 * | Wrappers for robust I/O  routines |
 * ------------------------------------
 */
ssize_t Rio_readn(int fd, void *usrbuf, size_t n) {
    ssize_t rc;
    if ((rc = rio_readn(fd, usrbuf, n)) < 0)
        unix_error("Rio_readn error");
    return rc;
}

void Rio_writen(int fd, void *usrbuf, size_t n) {
    if (rio_writen(fd, usrbuf, n) != n)
        unix_error("Rio_writen error");
}

void Rio_readinitb(rio_t *rp, int fd) {
    rio_readinitb(rp, fd);
}

ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) {
    ssize_t rc;
    if ((rc = rio_readlineb(rp, usrbuf, maxlen)) < 0)
        unix_error("Rio_readlineb error");
    return rc;
}

ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n) {
    ssize_t rc;
    if ((rc = rio_readnb(rp, usrbuf, n)) < 0)
        unix_error("Rio_readnb error");
    return rc;
}
/* --------------------------------
 * | Client/server helper function |
 * --------------------------------
 */

/*
 * open_clientfd - Open connection to server at <hostname, port> and
 *    return a socket descriptor ready for reading and writing. This
 *    function is reentrant and protocol-independent.
 *
 *    On errror, returns:
 *      -2 for getaddrinfo error
 *      -1 with errno set for other errors.
 */
int open_clientfd(char *hostname, char *port) {
    int clientfd, rc;
    struct addrinfo hints, *listp, *p;

    /* Get a list of potenial server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;   /* Open a connection */
    hints.ai_flags = AI_NUMERICSERV;   /* Using a numeric port arg. */
    hints.ai_flags = AI_ADDRCONFIG;    /* REcommended for connections */
    if ((rc = getaddrinfo(hostname, port, &hints, &listp)) < 0) {
        fprintf(stderr, "getaddrinfo failed (%s:%s): %s\n", hostname, port, gai_strerror(rc));
        return -2;
    }

    for (p = listp; p; p = p->ai_next) {
        /* Create a socket descriptor */
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;
    
        /* Connect to the server */
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break;      /* Success */
        if (close(clientfd) < 0) {  /* Connect failed, try another */
            fprintf(stderr, "open_clientfd: close failed: %s\n", strerror(errno));
            return -1;
        }
    }

    freeaddrinfo(listp);
    if (!p)             /* All connects failed */
        return -1;
    return clientfd;
}

/*
 * open_listenfd - Open and return a listening socket on port. This
 *   function is reetrant and protocol-independent.
 *
 *   On error, retruns:
 *      -2 for getaddinfo error
 *      -1 wirh errno set for other errors.
 */
int open_listenfd(char *port) {
    struct addrinfo hints, *listp, *p;
    int listenfd, rc, optval = 1;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    if ((rc = getaddrinfo(NULL, port, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo failed (port %s): %s\n", port, gai_strerror(rc));
        return -2;
    }

    for (p = listp; p; p = p->ai_next) {
        /* Create a socket descriptor */
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue;       /* Socket failed, try the next */

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
                (const void *)&optval, sizeof(int));

        /* Bind the descriptor to the address */
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break;          /* Success */
        if (close(listenfd) < 0) {  /* Bind failed, try the next */
            fprintf(stderr, "open_listenfd close failed: %s\n", strerror(errno));
            return -1;
        }
    }

    freeaddrinfo(listp);
    if (!p)
        return -1;

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0) {
        close(listenfd);
        return -1;
    }
    return listenfd;
}

/* ----------------------------------------------------- 
 * | Wrappers for reetrant protocol-independent helpers |
 * ------------------------------------------------------
 */
int Open_clientfd(char *hostname, char *port) 
{
    int rc;

    if ((rc = open_clientfd(hostname, port)) < 0) 
        unix_error("Open_clientfd error");
    return rc;
}

int Open_listenfd(char *port) 
{
    int rc;

    if ((rc = open_listenfd(port)) < 0)
        unix_error("Open_listenfd error");
    return rc;
}
