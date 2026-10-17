#include "vector.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vec_t init_null_vec()
{
    return (vec_t){.data = nullptr, .capacity = 0, .size = 0};
}

/*  vec_t* vec := nullptr is vacuously true
    otherwise, see null_vec as defined above
*/
static bool is_null_vec(vec_t* vec)
{
    // ASSERT: vec != nullptr
    return vec == nullptr || (vec->data == nullptr && vec->size == 0 && vec->capacity == 0);
}

static bool is_empty_vec(vec_t* vec)
{
    return !is_null_vec(vec) && vec->size == 0;
}

bool init_empty_vec(vec_t* vec)
{
    return init_vec(vec, DEFAULT_CAPACITY);
}

bool init_vec(vec_t* vec, size_t new_cap)
{
    if (vec == nullptr) {
        return false;
    }
    if (new_cap == 0) {
        *vec = init_null_vec();
        return true;
    }
    if (new_cap > MAX_CAPACITY) {
        return false;
    }
    void* new_data = malloc(sizeof(data_t) * new_cap);
    if (new_data == nullptr) {
        return false;
    }
    vec->data = (data_t*)new_data;
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

bool grow_vec(vec_t* vec, size_t new_capacity)
{
    if ((vec->capacity >= MAX_CAPACITY) || (new_capacity >= MAX_CAPACITY) ||
        new_capacity < vec->capacity) {
        return false;
    }

    void* new_data = realloc(vec->data, sizeof(data_t) * new_capacity);
    if (new_data == nullptr) {
        return false;
    }
    vec->data = new_data;
    vec->capacity = new_capacity;
    return true;
}

bool grow_vec_default(vec_t* vec)
{
    // grow vector
    if ((vec->capacity >= MAX_CAPACITY) || (vec->size >= (MAX_CAPACITY - 1))) {
        return false;
    }
    size_t new_capacity = vec->capacity >= (MAX_CAPACITY / 2) ? MAX_CAPACITY : (2 * vec->capacity);
    return grow_vec(vec, new_capacity);
}

bool push_back_vec(vec_t* vec, data_t new_element)
{
    if (is_null_vec(vec) && !init_vec(vec, DEFAULT_CAPACITY)) {
        return false; // there was indeed a better way
    }
    if (vec->size >= vec->capacity && !grow_vec_default(vec)) {
        return false;
    }
    vec->data[vec->size] = new_element;
    vec->size++;
    return true;
}

bool pop_back_element(vec_t* vec, data_t* old_element)
{
    if (is_null_vec(vec) || is_empty_vec(vec)) {
        return false;
    }
    vec->size--;
    if (old_element != nullptr) {
        *old_element = vec->data[vec->size];
    }
    return true;
}

bool insert_vec(vec_t* vec, size_t index, data_t new_element)
{
    if (vec == nullptr) {
        return false; // no vector???
    }
    // vec->data == nullptr is not necessarily a fail condition
    // but combined with index != 0, it is
    if (is_null_vec(vec)) {
        if (index != 0 || !init_vec(vec, DEFAULT_CAPACITY)) {
            return false;
        }
        return push_back_vec(vec, new_element);
    }
    // ASSERT: vec != nullptr, vec->data != nullptr, 1 <= index <= vec->size <= vec->capacity,
    if ((index > vec->size) || (vec->size >= vec->capacity && !grow_vec_default(vec))) {
        return false;
    }

    const size_t n_bytes = (sizeof(data_t)) * (vec->size - index);
    memmove((vec->data) + index + 1, (vec->data) + index, n_bytes);
    vec->size++;
    vec->data[index] = new_element;
    return true;
}

bool erase_vec(vec_t* vec, size_t index, data_t* old_element)
{
    if (vec == nullptr || index >= vec->size) {
        return false;
    }
    if (old_element != nullptr) {
        *old_element = vec->data[index];
    }

    const size_t n_bytes = (sizeof(data_t)) * (vec->size - index);
    memmove(vec->data + index, vec->data + index + 1, n_bytes);
    vec->size--;
    return true;
}

void print_vec(vec_t vec)
{
    fputs("[", stdout);
    for (size_t i = 0; i < vec.size; i++) {
        if (i > 0) {
            fputs(", ", stdout);
        }
        printf("%d", vec.data[i]);
    }
    fputs("]\n", stdout);
}

bool resize_vec(vec_t* vec, size_t new_size)
{
    if (vec == nullptr || new_size >= MAX_CAPACITY) {
        return false;
    }

    if (vec->size >= new_size) {
        vec->size = new_size;
        return true;
    }

    if (new_size > vec->capacity) {
        size_t new_cap = new_size >= (MAX_CAPACITY / 2) ? MAX_CAPACITY : 2 * new_size;
        if (!grow_vec(vec, new_cap)) {
            return false;
        }
    }

    size_t old_size = vec->size;
    const size_t n_bytes = (sizeof(data_t)) * (new_size - old_size);
    memset(vec->data + old_size, (data_t)0, n_bytes);
    vec->size = new_size;
    return true;
}

bool set_vec(vec_t* vec, size_t index, data_t new_element)
{
    if (vec == nullptr || index >= vec->size) {
        return false;
    }
    vec->data[index] = new_element;
    return true;
}

bool get_vec(vec_t vec, size_t index, data_t* out_val)
{
    if (out_val == nullptr || index >= vec.size) {
        return false;
    }
    *out_val = vec.data[index];
    return true;
}

bool reserve_vec(vec_t* vec, size_t reserve_cap)
{
    if (vec == nullptr) {
        return false;
    }

    if (reserve_cap <= vec->capacity) {
        return true;
    }

    return grow_vec(vec, reserve_cap);
}