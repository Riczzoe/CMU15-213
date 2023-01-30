#include <stdio.h>

int mystrend(char *s, char *t);
void mystrncpy(char *s, char *ct, int n);
char mystrncat(char *s, char *ct, int n);
int mystrcmp(char *cs, char *ct, int n);

int main() {
    char s[10];
    char t[] = "hello";
    mystrncpy(s, t, 6);
    printf("%s\n", s);
    return 0;
}

int mystrend(char *s, char *t) {
    char *begins = s;               /* remenber beginning of strings        */
    char *begint = t;

    while (*s++) {}                 /* end of the string                    */
    while (*t++) {}

    for ( ; *s == *t; s--, t--) {
        if (t == begint || s == begins) {
            break;
        }
    }

    if (*s == *t && t == begint && *s != '\0') {
        return 1;
    }
    return 0;

}


void mystrncpy(char *s, char *ct, int n) {
    while (*ct && n-- > 0) {
        *s++ = *ct++;
    }

    while (n-- > 0) {
        *s++ = '\0';
    }
}
char strncat(char *s, char *ct, int n) {
    while (*s++ == *t++) {
        if (*s == '\0' || --n <= 0) {
            return 0;
        }
    }
    return *s - *t;

}
/* int strcmp(char *cs, char *ct, int n); */
