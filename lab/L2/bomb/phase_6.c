void phase_6(string input) {
    int array[6];
    /*
     *  These six numbers are between 1 and 6, and each number
     *  is not equal to each other.
     */
    for (int i = 0; i < 6; i++) {
        if (a[i] > 6 || a[i] < 0) {
            bomb();
        }

        for (int j = i + 1; j <= 5; i++) {
            if (a[j] == a[i]) {
                bomb();
            }
        }
    }

    /*
     *Let each term be equal to 7 minus the value of the term itself.
     */
    for (int i = 0; i < 6; i++) {
        int edx = 7;
        a[i] = edx - a[i];
    }


    long b[6];
    for (int i = 0; i < 6; i++) {
        if (a[i] <= 1) {
            b[i] = 0x6032d0;
            
            /*  可去    */
            if (++i == 6) {
                break;
            }
        } else {
            int k = 2;
            while (a[i] != k)
                k++;
            b[i] = 0x6032d0 + 8 * (k - 1);
        }
    }

    for (int i = 0; i <= 4; i++) {
        *((long *)b[i] + 1) = b[i + 1];
    }
    *((long *)b[5]) = 0;


    int i = 5;
    do {
        
        i--;
    } while (i > 0)
}
