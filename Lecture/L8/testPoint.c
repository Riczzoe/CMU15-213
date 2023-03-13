#include    <stdio.h>

int main() {
    int A[3] = {1, 2, 3};
    int (*A4[3]);
    int (*A5[3])[5];

    printf("size of A4: %ld\n", sizeof(A4));
    printf("size of A5: %ld\n", sizeof(A5));

    int *p = A;
    printf("This is printf *p + 1: %d\n", *p++);
    printf("This is p: %d\n", *p);
    printf("This is printf 1 + *p: %d\n", *(1 + p));
    return 0;
}
