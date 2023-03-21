#include    <stdio.h>
#include    <stdlib.h>

typedef long data_t;                /*  Type of element in vector   */

/* Create abstract data type for vector */
typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr newVec(long len) {
    /* Allocate header structure */
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec)); 
    data_t *data = NULL;

    if (!result) {
        return NULL;                /*  Couldn't allocate storage   */
    }

    result->len = len;
    if (len > 0) {
        data = (data_t *) malloc(sizeof(data_t));
        if (!data) {
            free(result);
            return NULL;
        }
    }

    result->data = data;            /* Data will be either NULL or allocated array  */
    return result;
}

/*
 * Retrieve vector element and store at dest.
 * Return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, long index, data_t *dest) {
    if (index < 0 || index >= v->len) {
        return 0;
    }
    *dest = v->data[index];
    return 1;
}

long vec_length(vec_ptr v) {
    return v->len;
}

#define     IDENT   0
#define     OP      +

data_t *get_vec_start(vec_ptr v) {
    return v->data;
}

/* Implemention with maximum use of data abstrauction   */
void combine1(vec_ptr v, data_t *dest) {
    long i;
    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void combine2(vec_ptr v, data_t *dest) {
    long i;
    *dest = IDENT;
    long length = vec_length(v);
    for (i = 0; i < length; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void combine3(vec_ptr v, data_t *dest) {
    long i;

    *dest = IDENT;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    for (i = 0; i < length; i++) {
        *dest = *dest OP data[i];
    }
}


void combine4(vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    for (i = 0; i < length; i++) {
        acc = acc OP data[i];
    }

    *dest = acc;
}

int main(void) {
    long res = 0;
    long *a = (long *) malloc(sizeof(long) * 20);
    vec_rec v;
    v.data = a;
    v.len = 20;

    combine1(&v, &res);
    combine2(&v, &res);
    combine3(&v, &res);
    combine4(&v, &res);

    free(a);


    return 1;
}
