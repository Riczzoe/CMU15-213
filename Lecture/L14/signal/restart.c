#include "mylib.h"

sigjmp_buf buf;

void handler(int sig) {
   siglongjmp(buf, 1);
}

int main() {
    if (!sigsetjmp(buf, 1)) {
        Signal(SIGINT, handler);
        printf("Starting nosafe\n");
        Sio_puts("Starting sio\n");
    } else {
        printf("restarting nosafe\n");
        Sio_puts("restarting sio\n");
    }
        


    while (1) {
        Sleep(1);
        Sio_puts("processing...\n");
    }

    exit(0);
}
