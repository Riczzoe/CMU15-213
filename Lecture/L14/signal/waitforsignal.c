#include "mylib.h"

volatile sig_atomic_t pid;

void sigchld_handler(int sig) {
    int olderrno = errno;
    pid = waitpid(-1, NULL, 0);
    errno = olderrno;
}

void sigint_handler(int sig) {
    exit(0);
}

int main() {
    sigset_t mask_all, mask_one, prev;

    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGINT, sigint_handler);
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);

    while (1) {
        Sigprocmask(SIG_BLOCK, &mask_one, &prev);
        if (Fork() == 0) 
            exit(0);

        pid = 0;
        while (!pid) 
            sigsuspend(&prev);

        Sigprocmask(SIG_SETMASK, &prev, NULL);

        /* #<{(| Wait for SIGCHLD to be received (wasteful) |)}># */
        /* while (!pid) */
        /*     ; */
        
        /* A better way to wait for SIGCHLD 
         * But Race condition exists
         */
        /* while (!pid) */
            /* pause(); */

        /* we can use sleep() 
         */
        /* while (!pid) */
            /* sleep(1); */



        printf(".");
    }
    exit(0);
}
