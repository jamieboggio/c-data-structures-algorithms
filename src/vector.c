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

// index = 34, old_capacity = 34
size_t calculate_new_capacity(size_t index, size_t old_capacity)
{
    // 0 <= ret <= MAX_CAPACITY - invariant

    if (index > old_capacity) {
        if (index > MAX_CAPACITY / 2) {
            return MAX_CAPACITY;
        }
        return 2 * index;
    }
    if (old_capacity > (MAX_CAPACITY / 2)) {
        return MAX_CAPACITY;
    }
    // 34 >=? 16 --> yes
    //     --> 2 * 34 = 68
    size_t wish_capacity =
            (old_capacity >= (DEFAULT_CAPACITY / 2)) ? (2 * old_capacity) : DEFAULT_CAPACITY;
    return wish_capacity;
}

bool insert_vec(vec_t* vec, size_t index, data_t new_element)
{
    if (vec == nullptr || index >= MAX_CAPACITY) {
        return false;
    }
    const size_t old_capacity = vec->capacity;
    if (index >= old_capacity) {
        if (index >= MAX_CAPACITY) {
            return false;
        }
        const size_t new_capacity = calculate_new_capacity(index, old_capacity);
        void* new_data = realloc(vec->data, new_capacity * sizeof(data_t));
        if (new_data == nullptr) {
            return false;
        }
        vec->capacity = new_capacity;
        vec->data = (data_t*)new_data;
        assert(new_capacity >= old_capacity);
        memset((vec->data) + old_capacity, 0, (new_capacity - old_capacity));
    }
    vec->data[index] = new_element;
    vec->size++;
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
