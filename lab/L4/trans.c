/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32) {
        transpose_32(M, N, A, B);
    } else if (M == 64) {
        transpose_64(M, N, A, B);
    } else {
        transpose_61(M, N, A, B);
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 
char transpose_32_desc[] = "Transpose 32x32";
void transpose_32(int M, int N, int A[N][M], int B[M][N]) {
    int blockSize = 8;
    int en = blockSize * (M / blockSize);
    int i, j, ii, jj, tmp, index;
    for (i = 0; i < en; i += blockSize) {
        for (j = 0; j < en; j+= blockSize) {
            for (ii = i; ii < i + blockSize; ii++) {
                for (jj = j; jj < j + blockSize; jj++) {
                    /* if ii == jj, then the element of A[ii][jj] and b[jj][ii]
                     * are in the same cache block .
                     *
                     * And the improtant thing is that this happens only 
                     * blockSize times in a digonal block. so we can just store 
                     * the element of A[ii][jj], and does not immediately assign
                     * it to B[jj][ii].
                     */
                    if (ii != jj) {
                        B[jj][ii] = A[ii][jj];
                    } else {
                        tmp = A[ii][jj];
                        index = ii;
                    }
                }
                /* digonal conflict miss only happens when i = j */
                if (i == j) {
                    B[index][index] = tmp;
                }
            }
        }
    }
}

void transpose_64(int M, int N, int A[N][M], int B[M][N]) {

}

void transpose_61(int M, int N, int A[N][M], int B[M][N]) {

}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

