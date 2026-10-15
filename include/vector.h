#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>

typedef struct {
    int* data;
    size_t len;
    size_t capacity;
} vec_int_t;

#endif // _VECTOR_H_
