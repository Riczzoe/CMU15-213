#define     N   16

typedef int fix_matrix[N][N];

void fix_set_diag(fix_matrix A, int val) {
    int *Abase = &A[0][0];
    long i = 0;
    long Aend = N * ( N + 1);

    do {
        *(Abase + i) = val;
        i += N + 1;
    } while (i != Aend);
}
