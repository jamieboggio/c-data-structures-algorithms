#ifndef DSA_INCLUDE_VECTOR_H
#define DSA_INCLUDE_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef int data_t;

typedef struct {
    data_t* data;
    size_t len;
    size_t capacity;
} vec_t;

vec_t init_empty_vec();
vec_t init_vec(size_t new_cap, bool *success);
void free_vec(vec_t *vec);

#endif // DSA_INCLUDE_VECTOR_H
