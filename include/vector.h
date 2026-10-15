#ifndef DSA_INCLUDE_VECTOR_H
#define DSA_INCLUDE_VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef int data_t;

const static size_t MAX_CAPACITY = SIZE_MAX / (sizeof(data_t));
const static size_t DEFAULT_CAPACITY = 32UL;

typedef struct {
    data_t* data;
    size_t size;
    size_t capacity;
} vec_t;

vec_t init_empty_vec();
vec_t init_vec(size_t new_cap, bool* success);
void free_vec(vec_t* vec);
bool insert_vec(vec_t* vec, size_t index, data_t new_element);

#endif // DSA_INCLUDE_VECTOR_H
