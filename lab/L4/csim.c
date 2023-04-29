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

/* define the data structure of cache */
typedef struct line_tag {
    int vaild:1;
    long tag;
} line_t;

typedef struct set_tag {
    line_t *lines;
} set_t;

typedef struct cache_tag {
    set_t *sets;
} cache_t;

static void printUsage(char *argv[]);
static void checkArgsSetInitArg(int argc, char *argv[]);

static cache_t *cache;
static void freeCache();
static void initCache();

int main(int argc, char *argv[])
{
    checkArgsSetInitArg(argc, argv);
    initCache();
    freeCache();
    printSummary(hitCount, missCount, evictionCount);
    return 0;
}

/**
 * initCache - init the cache.
 */
static void initCache() {
    printf("setsNum: %d, linesNum: %d, blockSize: %d\n", 
            setsNum, linesNum, blockSize);
    cache = (cache_t *) malloc(sizeof(cache_t));
    if (!cache) {
        printf("No enough memory!\n");
        exit(EXIT_FAILURE);
    }

    cache->sets = (set_t *) malloc(sizeof(set_t) * setsNum);
    if (!cache->sets) {
        printf("No enough memory!\n");
        free(cache);
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < setsNum; i++) {
        line_t *lines = (line_t *) malloc(sizeof(line_t) * linesNum);
        if (!lines) {
            printf("No enough memory!\n");
            freeCache();
            exit(EXIT_FAILURE);
        }

        int j;
        for (j = 0; j < linesNum; j++) {
            line_t line = lines[j];
            line.vaild = 0;
        }

        cache->sets[i].lines = lines;
    }
}

/**
 * freeCache - free the malloc memory of cache.
 */
static void freeCache() {
    if (!cache) {
        return;
    }
    if (!cache->sets) {
        free(cache);
        return;
    }

    int i;
    for (i = 0; i < setsNum; i++) {
        set_t set = cache->sets[i];
        if (set.lines) {
            free(set.lines);
        }
    }
    free(cache->sets);
    free(cache);
}

/**
 * checkArgsSetInitArg - check the args are valid or not.
 *                       if valid, init the args.
 *                       if not valid, print the usage and exit.
 * @argc: the number of args.
 * @argv: the args.
 */
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
                /* invalid args */
                printUsage(argv);
                exit(EXIT_FAILURE);
        }
    }

    /* if the compulsory args are not set, or set to 0, 
     * print the usage and exit. 
     */
    if (setsNum <= 0 || linesNum <= 0 || blockSize <= 0) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(EXIT_FAILURE);
    }
}

/**
 * printUasge - print the usage of this program.
 * @argv: the argvs.
 */
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

