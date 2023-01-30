#include <stdio.h>

int main() {
    char a[] = "0123456700";
    char d[] = "000000000";
    char *b = d;
    
    printf("%s\n", b);
    for (int i = 0; i < 8; i++) {
        *b++ = i + 1 + '0';
        printf("%s\n", d);
    }
    char *p = a + 7;
    printf("%c\n", *p);
    printf("%s\n", a);

    /* *p++ = *(a + 1); */
    /* printf("%c, %c\n", *a, *(a + 1)); */
    printf("Now chang array a.\n");
    *p++ = '8';
    printf("%s\n", a);
    printf("%c\n", *p);
    char c = *--p;
    printf("%c\n", c);
    printf("%c\n", *p);
    return 0;
}
