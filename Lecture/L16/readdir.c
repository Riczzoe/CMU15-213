#include "mylib.h"

DIR *Opendir(const char* name);
struct dirent *readdir(DIR *dirp);
int Closedir(DIR *dirp);

int main(int argc, char **argv) {
    DIR *streamp;
    struct dirent *dep;

    streamp = Opendir(argv[1]);
    errno = 0;
    while ((dep = readdir(streamp)) != NULL) {
        printf("Found file: %s\n", dep->d_name);
    }

    if (!errno) 
        unix_error("readdir error");

    Closedir(streamp);
    exit(0);
}
