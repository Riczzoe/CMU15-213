#include "mylib.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s<hex>\n", argv[0]);
        exit(0);
    }
    
    char buf[64];
    struct in_addr inaddr;
    uint32_t addr;

    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htonl(addr);
    addr = htonl(addr);

    char *addrstring = "0x8002c2f2";
    inet_ntop(AF_INET, &addr, buf, 64);
    
    printf("%s\n", buf);
    exit(0);
    
}
