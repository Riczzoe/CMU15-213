#include    <stdio.h>

int main () {
    struct s1 {
        short i;
        short j;
        int k;
    } S1;

    struct s2 {
        short i;
        int k;
        short j;
    } S2;

    printf("This is size of a struct { s, s, i}: %ld\n", sizeof(S1));
    printf("This is size of a struct { s, i, s}: %ld\n", sizeof(S2));

    return 0;
}
