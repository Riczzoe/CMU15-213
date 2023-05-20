#include "mylib.h"

void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, 
        size_t hostlen, char *serv, size_t servlen, int flags);
void Freeaddrinfo(struct addrinfo *res);


int main(int argc, char **argv) {
    struct addrinfo *p, *listp, hints;
    struct sockaddr_in *sp;
    char buf[MAXLINE];
    int rc, flags;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;          /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM;    /* Connections only */

    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    /* Walk the list and display each IP address */
    flags = NI_NUMERICHOST; /* Display address string instead of domain name */
    for (p = listp; p; p = p->ai_next) {
        sp = (struct sockaddr_in *)p->ai_addr;
        inet_ntop(AF_INET, &(sp->sin_addr), buf, MAXLINE);
        printf("%s\n", buf);
    }
    
    Freeaddrinfo(listp);
    exit(0);
}
