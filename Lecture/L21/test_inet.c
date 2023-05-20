#include <stdio.h>
#include <arpa/inet.h>

int main() {
    char *addr1 = "0.0.0.0";
    char *addr2 = "128.2.194.242";

    char *dst1, *dst2;
    inet_pton(AF_INET, addr1, &dst1);
    printf("inet_pton: %s -> %x\n", addr1, dst1);
    inet_pton(AF_INET, addr2, &dst2);
    printf("inet_pton: %s -> %x\n", addr2, dst2);

    return 0;
}
