long loop_while(long a, long b) {
    long result = 1;
    while (a < b) {
        result += a * b;
        a++;
    }
    return result;
}
