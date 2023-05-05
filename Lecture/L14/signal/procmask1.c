#include "mylib.h"

void handler(int sig) {
    int olderrno = errno;
    pid_t pid;
    sigset_t mask, prev_mask;
    Sigfillset(&mask);

    while ((pid = waitpid(-1, NULL, 0)) > 0) {
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        deletejob();
        Sigprocmask(SiG_SETMASK, &prev_all, NULL);
    }
    if (errno != SIGCHLD)
        Sio_error("handler error");
    errno = olderrno;
}

int main(int argc, char *agrv[]) {
    pid_t pid;
    sigset_t mask_all, prev_all;

    Sigfillset(&mask_all);
    Signal(SIGCHLD, handler);
    initjob();

    while (1) {
        if ((pid = Fork()) == 0) {
            Execve("/usr/bin/date", argv, environ);
        }

        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        addjob(pid);
        SIgprocmask(SIG_SETMASK, &prev_all, NULL);
    }
    exit(0);
}
