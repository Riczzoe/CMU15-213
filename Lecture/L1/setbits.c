#include <stdio.h>

int setbits(unsigned x, int p, int n, unsigned y);
int invert(unsigned x, int p, int n);
int rightrot(unsigned x, int n);
int bitcount(unsigned x);

int main() {
    printf("%d\n", bitcount(3));
    return 0;
}


int setbits(unsigned x, int p, int n, unsigned y) {
    /* xxx...x000x...xxx    x
     * 000...0yyy0...000    y
     * ----------------------
     * xxx...xyyyx...xxx    x
     *
     * 1. xxx...x000x...xxx 
     * xxx...xxxxx...xxx    x
     * 111...10001...111    -> ~000...000 ->   111...111 << n -->  ~111...1000
     *                                                                  |
     *                000...01110...000  <- 000...0111 << (p + 1 - n) <-
     * ----------------------
     * xxx...x000x...xxx
     */

    return x & ~(~(~0 << n) << (p + 1 - n)) |
          (y &   ~(~0 << n) << (p + 1 - n));
}

int invert(unsigned x, int p, int n) {
    return x ^ (~(~0 << n) << (p + 1 - n));
}

int rightrot(unsigned x, int n) {
    int wordLength(void);
    int rbit;

    while (n-- > 0) {
        rbit = (x & 1) << (wordLength() - 1);
        x = x >> 1;
        x = x | rbit;
    }
    return x;
}

int wordLength(void) {
    int i;
    unsigned v = (unsigned) ~0;
    for (i = 1; (v = v >> 1) > 0; i++) 
        ;
    return i;
}

int bitcount(unsigned x) {
    int nb;
    for (nb = 0; x != 0; x >>= 1) {
        if (x & 1)
            nb++;
    }
    return nb;
}
