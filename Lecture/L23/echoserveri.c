#include "mylib.h"

void echo(int connfd);

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char hostname[MAXLINE], port[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, 
                    hostname, MAXLINE,
                    port, MAXLINE, 0);
        printf("Connectd to (%s, %s)\n", hostname, port);
        echo(connfd);
        close(connfd);
    }
    exit(0);
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
