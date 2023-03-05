void fun_b() {
    int sum = 0;
    for (int i = 0; i < 11; i++) {
        if (i & 1) 
            continue;
        sum += i;
    }
}
