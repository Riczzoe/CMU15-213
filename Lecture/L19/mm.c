extern int mm_init(void);
extern void *mm_malloc(size_t size);
extern void mm_free(void *ptr);

/* Basic constants and macros */
#define WISZE       4           /* Word and header.footer size (bytes) */
#define DSIZE       8           /* Double word size (bytes0 */
#define CHUNKSIZE   (1 << 12)   /* Extend heap by this amout (bytes) */

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))

/* Read the size and allocated fileds from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)        ((char *)(bp) - WSIZE)
#define FTRP(bp)        ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous block */
#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE((char *)(bp) - WSIZE))
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE((char *)(bp) - DSIZE))

/* Private global variables */
static void *heap_list      /* Points to the second word of prologue block */

static void *coalesce(void *bp) {
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    /* previous and next block are allocated */
    if (prev_alloc && next_alloc)
        return bp;

    /* previous block are allocated and next block are free */
    else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }

    /* previous block are free and next block are allocated */
    else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    /* previous and next block are free */
    else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
                GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    return bp;
}

void mm_free(void *bp) {
    size_t size = GET_SIZE(HDRP(bp));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    Coalesce(bp);
}

static void *extend_heap(size_t words) {
    char *p;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long) (bp = mem_sbrk(size)) == -1)
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));           /* Free block header */
    PUT(FTRP(bp), PACK(size, 0));           /* Free block footer */
    PUT(HDRP(NECT_BLKP(bp)), PACK(0, 1));   /* new epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

int mm_init(void) {
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *) -1)
            return -1;

    PUT(heap_listp, 0);                             /* Alignmernt padding*/
    PUT(heap_listp + (1 * WSIZE), PACK(DISZE, 1));  /* Prologue header */
    PUT(heap_listp + (2 * WSIZE), PACK(DISZE, 1));  /* Prologue footer */
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));      /* Epilogue header */
    heap_listp += (2 * WSIZE);

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;
    return 0;
}

static void *find_fit(size_t asize) {
    void *p;

    for (p = heap_list; GET_SIZE(HDRP(p)) > 0; p = NEXT_BLKP(p)) 
        if ((GET_SIZE(HDRP(p)) >= size) && !GET_ALLOC(HDRP(p)))
            retrun p;

    return NULL;
}

static void place(void *bp, size_t asize) {
    size_t block_size = GET_SIZE(HDRP(bp));

    if (block_size - asize >= 2 * DSIZE) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(block_size - asize, 0));
        PUT(FTRP(bp), PACK(block_size - asize, 0));
    } else {
        PUT(HDRP(bp), PACK(block_size, 1));
        PUT(FTRP(bp), PACK(block_size, 1));
    }
}

void *mm_malloc(size_t size) {
    size_t asize;       /* Adjusted block size */
    void *bp;
    
    /* Ignore spurious request */
    if (size == 0) 
        return NULL;

    /* Adjust block size to include overhead and alignment reqs */
    if (size < DISZE)
        asize = 2 * DSIZE;
    else
        asize = (DSIZE - 1 + size + DSIZE) / DSIZE * DSIZE;

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    extendSize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize / WSIZE)) == NULL) 
        return NULL;
    Place(bp, asize);
    return bp;
}
