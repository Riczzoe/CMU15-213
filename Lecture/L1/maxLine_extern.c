#include <stdio.h>
#define MAXLINE 1000                /* maximum input line length        */

int max = 0;
char longest[MAXLINE];
char line[MAXLINE];
int getaline(void);
void copy(void);

/* print the longest input line */
int main(int argc, char* argv[]) {
    int len;

    /* max = 0; */
    while ((len = getaline()) > 0) {
        if (len > max) {
            max = len;
            copy();
        }
    }

    if (max > 0) 
        printf("%s", longest);
    return 0;
}

int getaline() {
    int c, i;
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i) 
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

void copy() {
    int i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
