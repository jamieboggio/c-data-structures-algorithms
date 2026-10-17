#ifndef DSA_C_INCLUDE_SLIST_H
#define DSA_C_INCLUDE_SLIST_H

#include "node.h"
#include <stddef.h>

typedef struct slist_struct {
    size_t n;
    node* head;
    node* tail;
} slist_t;

slist_t init_slist();

void free_slist(slist_t* list);

data_t* push_front_slist(slist_t* list, data_t* new_element);

data_t* pop_front_slist(slist_t* list, data_t* out_element);

data_t* push_back_slist(slist_t* list, data_t* new_element);

data_t* pop_back_slist(slist_t* list, data_t* out_element);

data_t* insert_slist(slist_t* list, data_t* new_element, size_t index);

data_t* erase_slist(slist_t* list, data_t* out_element, size_t index);

node* find_slist(slist_t* list, data_t wish_element);

void reverse_slist(slist_t* list);

data_t* peek_front_slist(slist_t* list, data_t* out_element);

#endif // DSA_C_INCLUDE_SLIST_H