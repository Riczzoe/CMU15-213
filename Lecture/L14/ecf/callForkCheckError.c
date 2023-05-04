#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

/* Unix-style error */
void unix_error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void) {
    pid_t pid;

    if ((pid = fork()) < 0) 
        unix_error("fork error");
    return pid;
}
int main() {
    pid_t pid;
    pid = Fork();
    printf("pid = %d\n", pid);
    return 0;
}
