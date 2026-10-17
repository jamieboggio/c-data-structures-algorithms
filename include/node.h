#ifndef DSA_C_INCLUDE_NODE_H
#define DSA_C_INCLUDE_NODE_H

#include "data_t.h"
#include <stdlib.h>

typedef struct node {
    data_t val;
    struct node* next;
} node;

node* new_node(data_t x)
{
    node n = {.val = x, .next = nullptr};
    node* new_data = (node*)malloc(sizeof(node));
    if (new_data != nullptr) {
        *new_data = n;
    }
    return new_data;
}

#endif // DSA_C_INCLUDE_NODE_H