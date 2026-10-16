/**
 * @file vector.h
 * @brief Implements the vector container with data_t defined as int
 */

#ifndef DSA_INCLUDE_VECTOR_H
#define DSA_INCLUDE_VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef int data_t;

#define MAX_CAPACITY (PTRDIFF_MAX / (sizeof(data_t)))
#define DEFAULT_CAPACITY 32UL

typedef struct vec_struct {
    data_t* data;
    size_t size;
    size_t capacity;
} vec_t;

/**
 * @brief Initializes an empty vector
 *
 * @return vec_t
 */
vec_t init_empty_vec();

/**
 * @brief Initializes a vector with a specified capacity
 *
 * @param vec Pointer to the vector to initialize
 * @param new_cap The new capacity of the vector
 * @return true on success, false on failure
 */
bool init_vec(vec_t* vec, size_t new_cap);

/**
 * @brief Frees the memory allocated for the vector
 *
 * @param vec The vector to free
 */
void free_vec(vec_t* vec);

/**
 * @brief Adds an element to the end of the vector
 *
 * @param vec The vector to add the element to
 * @param new_element The element to add
 * @return true on success, false on failure
 */
bool push_back_vec(vec_t* vec, data_t new_element);

/**
 * @brief Removes the last element from the vector
 *
 * @param vec The vector to remove the element from
 * @param old_element A pointer to store the removed element
 * @return true on success (removal succeeds), false on failure (removal fails)
 */
bool pop_back_element(vec_t* vec, data_t* old_element);

/**
 * @brief Inserts an element at a specified index in the vector
 *
 * @param vec The vector to insert the element into
 * @param index The index at which to insert the element
 * @param new_element The element to insert
 * @return true on success, false on failure
 */
bool insert_vec(vec_t* vec, size_t index, data_t new_element);

/**
 * @brief Erases an element at a specified index from the vector
 *
 * @param vec The vector to erase the element from
 * @param index The index of the element to erase
 * @param old_element A pointer to store the erased element
 * @return true on success, false on failure
 */
bool erase_vec(vec_t* vec, size_t index, data_t* old_element);

/**
 * @brief Resizes the vector to a new capacity
 *
 * @param vec The vector to resize
 * @param new_capacity The new capacity of the vector
 * @return true on success, false on failure
 */
bool resize_vec(vec_t* vec, size_t new_capacity);

#endif // DSA_INCLUDE_VECTOR_H
