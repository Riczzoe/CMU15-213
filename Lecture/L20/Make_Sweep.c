typedef void *ptr;

/* isptr - If p is a pointer pointing to a word on allocated
 *    block, return the pointer to the block header; 
 *    otherwise, return NULL.
 */
ptr isPtr(ptr p);      

/* blockMarked - Return true if the block is marked. */
int blockMarked(ptr b);

/* markBlock - Mark the block. */
void markBlock(ptr b);

/* length - Return the length of the block. */
int length(ptr b);

/* unmarkBlock - Unmark the block. */
void unmarkBlock(ptr b);

/* nextBlock - Return the pointer to the next block. */
ptr nextBlock(ptr b);

void mark(ptr p) {
    if ((b = isPtr(b)) == NULL)
        return;
    if (blockMarked(b))
        return;
    markBlock(b);
    len = length(b);
    for (i = 0; i < len; i++)
        mark(b[i]);
    return;
}

void sweep(ptr b, ptr end) {
    while (b < end) {
        if (blockMarked(b))
            unmarkBlock(b);
        else if (blockAllocated(b))
            freeBlock(b);
        b = nextBlock(b);
    }
    return;
}
