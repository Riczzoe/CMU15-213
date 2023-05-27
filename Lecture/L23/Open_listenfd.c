int open_listenfd(char *port) {
    int listenfd, optval = 1;
    struct addrinfo *listp, *p, hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.sock_type = SOCK_STREAM;
    hints.ai_flags = AI_ADDRCONGIG;
    hints.ai_flags |= AI_NUMERICSERV;
    Getaddrinfo(NULL, prot, &hints, &listp);

    for (p = listp; p; p = p->ai_next) {
        if ((listenfd = socket(p->ai_family, p->sock_type, p->protocol)) < 0) {
            continue;
        }

        /* Set SO_REUSEADDR
         *
         * This is a socket option that tells the kernel that even 
         * if this port is busy (in the TIME_WAIT state), go ahead
         * and reuse it anyway. If it is busy, but with another state,
         * you will still get an address already in use error. It is
         * useful if your server has been shut down, and then restarted
         * right away while sockets are still active on its port.
         */
        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
                (const void *)&optval, sizeof(int));

        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break;
        close(listenfd);
    }

    Freeaddrinfo(listp);
    if (!p)
        return -1;

    if (listen(listenfd, LISTENQ) < 0) {
        close(listenfd);
        return -1;
    }
    return listenfd;
}
