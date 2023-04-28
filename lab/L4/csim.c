#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* more info about this error see:
 * https://stackoverflow.com/questions/22575940/getopt-not-included-implicit-declaration-of-function-getopt */
/* fix bug: implicit declaration of function ‘getopt’ */
#include <getopt.h>        
#include "cachelab.h"


static int setsNum = 0;         /* The number of sets */
static int linesNum = 0;        /* The number of lines per set */
static int blockSize = 0;       /* The number of bytes per block */
static int hitCount = 0;        /* The number of hits */
static int missCount = 0;       /* The number of misses */
static int evictionCount = 0;   /* The number of evictions */

static int verbose = 0;         /* The verbose flag */

static void printUsage(char *argv[]);
static void checkArgsSetInitArg(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    checkArgsSetInitArg(argc, argv);
    printSummary(hitCount, missCount, evictionCount);
    return 0;
}

static void checkArgsSetInitArg(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt) {
            case 'h':
                printUsage(argv);
                exit(EXIT_SUCCESS);
            case 'v':
                verbose = 1;
                break;
            case 's':
                setsNum = atoi(optarg);
                break;
            case 'E':
                linesNum = atoi(optarg);
                break;
            case 'b':
                blockSize = atoi(optarg);
                break;
            case 't':
                break;
            default:
                printUsage(argv);
                exit(EXIT_FAILURE);
        }
    }

    if (setsNum <= 0 || linesNum <= 0 || blockSize <= 0) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(EXIT_FAILURE);
    }
}

static void printUsage(char *argv[]) {
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n"
           "Options:\n"
           "  -h         Print this help message.\n"
           "  -v         Optional verbose flag.\n"
           "  -s <num>   Number of set index bits.\n"
           "  -E <num>   Number of lines per set.\n"
           "  -b <num>   Number of block offset bits.\n"
           "  -t <file>  Trace file.\n"
           "\n"
           "Examples:\n"
           "  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n"
           "  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n"
           , argv[0]);
}

