#include "vector.h"
#include <stdint.h>
#include <stdlib.h>

vec_t init_empty_vec()
{
    return (vec_t){.data = nullptr, .capacity = 0, .size = 0};
}

vec_t init_vec(size_t new_cap, bool* success)
{
    vec_t ret = init_empty_vec();
    if (new_cap == 0) {
        if (success != nullptr) {
            *success = true;
        }
        return ret;
    }
    if (new_cap > (SIZE_MAX) / sizeof(data_t)) {
        if (success != nullptr) {
            *success = false;
        }
        return ret;
    }
    void* data = malloc(sizeof(data_t) * new_cap);
    if (data == nullptr) {
        if (success != nullptr) {
            *success = false;
        }
        return ret;
    }
    ret.data = (data_t*)data;
    ret.capacity = new_cap;
    if (success != nullptr) {
        *success = true;
    }
    return ret;
}

size_t calculate_new_capacity(size_t old_capacity)
{
    if (old_capacity >= (MAX_CAPACITY / 2)) {
        return MAX_CAPACITY;
    }
    if (old_capacity == 0) {
        return DEFAULT_CAPACITY;
    }
    return 2 * old_capacity;
}

bool insert_vec(vec_t* vec, size_t index, data_t new_element)
{
    if (vec == nullptr || index >= MAX_CAPACITY) {
        return false;
    }
    const size_t old_capacity = vec->capacity;
    if (index >= old_capacity) {
        const size_t new_capacity = calculate_new_capacity(old_capacity);
        void* new_data = realloc(vec->data, new_capacity * sizeof(data_t));
        if (new_data == nullptr) {
            return false;
        }
        vec->capacity = new_capacity;
        vec->data = (data_t*)new_data;
        for (size_t i = old_capacity; i < new_capacity; i++) {
            vec->data[i] = (data_t)0;
        }
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
