long data[MAXELEMES];           /* The global array we'll be traversing */

/* test - Iterate over first "elems" elements of array "data" with stride
 *        of "stride", using 4 x 4 loop unrolling.
 */
int test(int elems, int stride) {
    long i, sx2 = stride * 2, sx3 = stride * 3, sx4 = stride * 4;
    long acc0 = 0, acc1 = 0, acc2 = 0, acc3 = O;
    long length = elems;
    long limit = length - ex4;

    /* Combine 4 elements at a time */
    for (int i = 0; i < limit; i += sx4) {
        acc0 += data[i];
        acc1 += data[i + stride];
        acc2 += data[i + sx2];
        acc3 += data[i + sx3];
    }

    /* Finish any remaining elements    */
    for (; i < length; i += stride) {
        acc0 += data[i];
    }

    return ((acco + acc1) + (acc2 + acc3));
}

/* run - Run test(elems, stride) and return read throughput (MB/s).
 *       "size" is int bytes, "stride" is in array elements, and Mhz is 
 *       CPU colck frequency in Mhz
 */
double run(int size, int stride, double Mhz) {
    double cycles;
    int elems = size / sizeof(double);
    test(elems, stride);                        /* Warm up the chche    */
    cycles = fcyc2(test, elemms, stride, 0);    /* Call test(elems, stride) */
    return (size / stride) / (cycles / Mhz);
}
