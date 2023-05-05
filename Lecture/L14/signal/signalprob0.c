#include "mylib.h"

void Sio_putl(long v);

volatile long counter = 2;

void handler(int sig) {
    sigset_t set, oldset;

    Sigfillset(&set);
    Sigprocmask(SIG_BLOCK, &set, &oldset);
    Sio_putl(--counter);
    Sigprocmask(SIG_SETMASK, &oldset, NULL);
    _exit(0);
}

int main() {
    pid_t pid;
    sigset_t set, oldset;

    printf("%ld", counter);
    fflush(stdout);

    Signal(SIGUSR1, handler);
    if ((pid = Fork()) == 0) {
        while (1)
            ;
    }

    Kill(pid, SIGUSR1);
    Waitpid(-1, NULL, 0);

    Sigfillset(&set);
    Sigprocmask(SIG_BLOCK, &set, &oldset);
    /* printf("%ld", ++counter); */
    Sio_putl(++counter);
    Sigprocmask(SIG_SETMASK, &oldset, NULL);

    return 0;
}
