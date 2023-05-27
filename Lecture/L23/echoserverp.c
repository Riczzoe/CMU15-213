#include "mylib.h"

void echo(int connfd);

void sigchld_handler(int sig) {
    while (waitpid(-1, 0, WNOHANG) > 0)
        ;
    return;
}

int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_storage clientaddr;
    socklen_t clientlen;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, &clientaddr, &clientlen);
        if (Fork() == 0) {
            close(listenfd);
            echo(connfd);
            close(connfd);
            exit(0);
        }
        close(connfd);
    }
}

void echo(int connfd) {
    size_t n;
    rio_t rio;
    char buf[MAXLINE];
    Rio_readinitb(&rio, connfd);

    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        printf("Server received %d bytes\n", (int)n);
        Rio_writen(connfd, buf, n);
    }
}
