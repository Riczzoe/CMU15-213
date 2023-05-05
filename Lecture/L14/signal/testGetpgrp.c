#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;
    if ((pid = fork()) == 0) {
        printf("child pid: %d\n", getpid());
        printf("child pgrp: %d\n", getpgrp());
        setpgid(0, 0);
        printf("child pid: %d\n", getpid());
        printf("child pgrp: %d\n", getpgrp());
        return 0;
    } else {
        pid = getpid();
        printf("parent pid: %d\n", pid);
        pid = getpgrp();
        printf("parent pgrp: %d\n", pid);
    }
    return 0;
}
