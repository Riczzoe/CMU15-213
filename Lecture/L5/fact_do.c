long fact_do(long n) {
    long result = 1;
    do {
        result *= n;
        n--;
    } while (n > 1);
    return result;
}
