#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* more info about this error see:
 * https://stackoverflow.com/questions/22575940/getopt-not-included-implicit-declaration-of-function-getopt */
/* fix bug: implicit declaration of function ‘getopt’ */
#include <getopt.h>        
#include "cachelab.h"

#define MAXLINE 20

static int setsNum = 0;         /* The number of sets */
static int linesNum = 0;        /* The number of lines per set */
static int blockSize = 0;       /* The number of bytes per block */
static char *fileName = NULL;   /* The name of the valgrind trace to replay */

static int hitCount = 0;        /* The number of hits */
static int missCount = 0;       /* The number of misses */
static int evictionCount = 0;   /* The number of evictions */

static int verbose = 0;         /* The verbose flag */

/* define the data structure of cache */
typedef struct line_tag {
    int valid;
    unsigned long tag;
    clock_t accessTime;
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
static FILE *getTraceFile();
static void simulateCache();
static void handleLoad(const unsigned long *addr);
static void handleStore(const unsigned long *addr);
static int checkHit(const set_t *set, const unsigned long tag);
static int needEviction(const set_t *set, const unsigned long tag);


int main(int argc, char *argv[])
{
    checkArgsSetInitArg(argc, argv);
    initCache();
    simulateCache();
    freeCache();
    printSummary(hitCount, missCount, evictionCount);
    return 0;
}

/* simulateCache - simulate the cache.
 *     Read the trace file line by line.
 *     If the operation is 'L', then call handleLoad function.
 *     If the operation is 'S', then call handleStore function.
 *     If the operation is 'M', then call handleLoad and handleStore function.
 *     If the operation is 'I', then ignore it.
 */
static void simulateCache() {
    FILE *traceFile = getTraceFile();
    char line[MAXLINE];

    char op;
    unsigned long addr;
    int size;
    while (fgets(line, MAXLINE, traceFile) != NULL) {
        sscanf(line, " %c %lx,%d", &op, &addr, &size);
        line[strlen(line) - 1] = ' ';
        if (verbose && line[0] != 'I') {
            printf("%s", line + 1);
        }
        switch (op) {
            case 'L':
                handleLoad(&addr);
                break;
            case 'S':
                handleStore(&addr);
                break;
            case 'M':
                handleLoad(&addr);
                handleStore(&addr);
                break;
            default:
                continue;
        }
        if (verbose) {
            printf("\n");
            /* printCache(); */
        }
    }
    fclose(traceFile);
}

static FILE *getTraceFile() {
    FILE *fp = fopen(fileName, "r");
    if (!fp) {
        printf("%s: No such file or directory\n", fileName);
        exit(EXIT_FAILURE);
    }
    return fp;
}

/* handleLoad - handle the load operation
 *    If hit, then hitCount++.
 *    If miss, then missCount++.
 *    If need eviction, then evictionCount++.
 */
static void handleLoad(const unsigned long *addr) {
    int setIndex = *addr / blockSize % setsNum;
    unsigned long tag = *addr / blockSize / setsNum;
    set_t *set = &(cache->sets[setIndex]);
    if (checkHit(set, tag)) {
        hitCount++;
        if (verbose) {
            printf(" hit");
        }
    } else {
        missCount++;
        if (verbose) {
            printf(" miss");
        }
        if (needEviction(set, tag)) {
            evictionCount++;
            if (verbose) {
                printf(" eviction");
            }
        }
    }
}

/* needEviction - check whether the cache need eviction.
 *     If all line of the set is valid and miss, then need eviction.
 *       return 1, otherwise return 0.
 */
static int needEviction(const set_t *set, const unsigned long tag) {
    int i;
    int min_index = 0;
    for (i = 0; i < linesNum; i++) {
        line_t *line = &(set->lines[i]);
        if (!line->valid) {
            line->valid = 1;
            line->tag = tag;
            line->accessTime = clock();
            return 0;
        } else {
            if (line->accessTime < set->lines[min_index].accessTime) {
                min_index = i;
            }
        }
    }
    
    line_t *evict_line = &(set->lines[min_index]);
    evict_line->valid = 1;
    evict_line->tag = tag;
    evict_line->accessTime = clock();
    return 1;
}

/* checkHit - check whether the cache hit or not.
 *     If hit, return 1, otherwise return 0.
 */
static int checkHit(const set_t *set, const unsigned long tag) {
    int i;
    for (i = 0; i < linesNum; i++) {
        line_t *line = &(set->lines[i]);
        if (line->valid && line->tag == tag) {
            line->accessTime = clock();
            return 1;
        }
    }
    return 0;
}



/* handleStore - handle the store operation 
 *     In this lab, the store operation is the same as the load 
 *     operation. So we just call the handleLoad function.
 */
static void handleStore(const unsigned long *addr) {
    handleLoad(addr);
}

/**
 * initCache - init the cache.
 */
static void initCache() {
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
            lines[j].valid = 0;
            lines[j].accessTime = 0;
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
        set_t *set = &(cache->sets[i]);
        if (set->lines) {
            free(set->lines);
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
                setsNum = 1 << atoi(optarg);
                break;
            case 'E':
                linesNum = atoi(optarg);
                break;
            case 'b':
                blockSize = 1 << atoi(optarg);
                break;
            case 't':
                fileName = optarg;
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
    if (setsNum <= 0 || linesNum <= 0 || blockSize <= 0 || !fileName) {
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

