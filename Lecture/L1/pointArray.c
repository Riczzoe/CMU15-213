#include    <stdio.h>
#include    <string.h>

#define     MAXLINES    5000        /* max #lines to be sorted              */

char *lineptr[MAXLINES];            /* pointers to text lines               */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main() {
    int nlines;                     /* number of input lines read           */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }

    printf("error: input too big to sort\n");
    return 1;
}

#define MAXLEN 1000                 /* max length of any input line         */
int getline(char *, int);

int readlines(char *lineptr[], int nlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nline >= MAXLINES || p = alloc(len) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return lines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines -- > 0) {
        printf("%s\n", *lineptr++);
    }
}
void qsort(char *lineptr[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) 
        return;
    swap(lineptr, left, (left + right) / 2);
    last = left;
    for (int i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(lineptr, ++last, left);
        }
    }
    swap(lineptr, left, last);
    qsort(lineptr, left, last - 1);
    qsort(lineptr, last, right);
}
void swap(char *v[], int i, int j);
