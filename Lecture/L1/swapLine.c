#inlcude    <stdio.h>

#define     MAXCOL      10          /* maximum column of input              */
#define     TABINC      8           /* tab increment size                   */

char line[MAXCOL];


int main() {
    int c, pos;

    for (pos = 0; (c = getchar()) != EOF; ) {
        if (++pos % MAXCOL == 0) {
            pos = 0;
            putchar('\n');
            putchar(c);
        }
    }
    return 0;
}
