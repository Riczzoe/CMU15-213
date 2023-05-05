#include "mylib.h"

void sigint_handler(int sig) {
    return;
}

int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");
    snooze(5);
    return 0;
}
