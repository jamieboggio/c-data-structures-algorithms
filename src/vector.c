#include "vector.h"
#include <stdint.h>
#include <stdlib.h>

vec_t init_empty_vec()
{
    return (vec_t){.data = nullptr, .capacity = 0, .len = 0};
}

vec_t init_vec(size_t new_cap, bool* success)
{
    vec_t ret = init_empty_vec();
    if (new_cap == 0) {
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

void free_vec(vec_t* vec)
{
    if (vec != nullptr) {
        free(vec->data);
        vec->data = nullptr;
        vec->len = 0;
        vec->capacity = 0;
    }
}
