sigset_t mask, prev_mask;

Sigemptyset(&mask);
Sigaddset(&mask, SIGINT);

/* Block SIGINT and save current signal mask */
Sigprocmask(SIG_BLOCK, &mask, &prev_mask);

/* code region that should not be interrupted by SIGINT */


/* Restore previous signal mask (unblock SIGINT) */
Sigprocmask(SIG_SETMASK, &prev_mask, NULL);

