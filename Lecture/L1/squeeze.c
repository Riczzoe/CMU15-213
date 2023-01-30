#include <stdio.h>

void squeeze(char* s1[], char* s2[]);

int main() {
    char s[] = "hello, john";
    char n[] = "ol";
    squeeze(s, n);
    printf("%s\n", s);
    return 0;
}

void squeeze(char* s1[], char* s2[]) {
    int i, j, k;

    for (i = k = 0; *s1[i] != '\0'; i++) {
        for (j = 0; *s2[j] != '\0' && *s2[j] != *s1[j]; j++) { }
        if (*s2[j] == '\0') {
            *s1[k++] = *s1[i];
        }
    }
    s1[k] = '\0';
}
