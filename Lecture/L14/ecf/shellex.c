#include "mylib.h"
#define MAXARGS     128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

int main() {
    char cmdline[MAXLINE]; /* Command line */

    while (1) {
        printf(">>> "); /* Prompt */
        Fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin)) 
            exit(0);

        eval(cmdline);
    }
}

/* eval - Evaluate a command line */
void eval(char *cmdline) {
    char *argv[MAXARGS];    /* Argument list execve() */
    char buf[MAXLINE];      /* Holds modified command line */
    int bg;                 /* Should the job run in bg or fg? */
    pid_t pid;              /* Process id */

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (!argv[0]) 
        return;             /* Ignore empty lines */

    if (!builtin_command(argv)) {
        /* Child runs user job */
        if ((pid = Fork()) == 0) { 
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found\n", argv[0]);
                exit(0);
            }
        }

        printf("!bg: %d\n", !bg);
        /* Parent waits for foreground job to terminate */
        if (!bg) {
            int status;
            if (waitpid(pid, &status, 0) < 0) 
                unix_error("waitfg: waitpid error");
        } else 
            printf("%d %s", pid, cmdline);
    }

    return;
}

/* If first arg is a builtin command, run it and return true */
int parseline(char *buf, char **argv) {
    char *delim;                        /* Points to first space delimiter  */
    int argc;                           /* Number of argc   */
    int bg;                             /* Background job?  */
    
    buf[strlen(buf) - 1] = ' ';         /* Replace tailing '\n' with space  */
    while (*buf && (*buf == ' '))       /* Ignore leading space */
        buf++;

    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) 
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0)                      /* Ignore blank line    */
        return 1;

    if (bg = (*argv[argc - 1] == '&')) {
        argv[--argc] = NULL;
    }

    return bg;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) {
    if (!strcmp(argv[0], "quit"))
        exit(0);
    if (!strcmp(argv[0], "&"))
        return 1;
    return 0;
}
