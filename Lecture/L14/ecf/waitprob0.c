#include "mylib.h"
#include <sys/wait.h>

int main() {
    if (Fork() == 0) {
        printf("a\n");
        fflush(stdout);
    } else {
        printf("b\n");
        fflush(stdout);
        waitpid(-1, NULL, 0);
    }
    printf("c\n");
    fflush(stdout);
    return 0;
}
