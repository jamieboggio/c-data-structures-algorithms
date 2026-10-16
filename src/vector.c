#include "vector.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

vec_t init_empty_vec()
{
    return (vec_t){.data = nullptr, .capacity = 0, .size = 0};
}

bool init_vec(size_t new_cap, vec_t* vec)
{
    if (vec == nullptr) {
        return false;
    }

    vec_t new_vec = init_empty_vec();
    if (new_cap == 0) {
        *vec = new_vec;
        return true;
    }

    if (new_cap > MAX_CAPACITY) {
        return false;
    }
    void* data = malloc(sizeof(data_t) * new_cap);
    if (data == nullptr) {
        return false;
    }
    vec->data = (data_t*)data;
    vec->size = 0;
    vec->capacity = new_cap;
    return true;
}

void free_vec(vec_t* vec)
{
    if (vec != nullptr) {
        free(vec->data);
        vec->data = nullptr;
        vec->size = 0;
        vec->capacity = 0;
    }
}

bool push_back_vec(vec_t* vec, data_t new_element)
{
    if (vec == nullptr) {
        return false;
    }
    if (vec->size >= vec->capacity) {
        // grow vector
        if ((vec->capacity >= MAX_CAPACITY) || (vec->size >= (MAX_CAPACITY - 1))) {
            return false;
        }
        size_t new_capacity =
                vec->capacity >= (MAX_CAPACITY / 2) ? MAX_CAPACITY : (2 * vec->capacity);
        void* new_data = realloc(vec->data, sizeof(data_t) * new_capacity);
    }
    vec->data[(vec->size)++] = new_element;
    return true;
}