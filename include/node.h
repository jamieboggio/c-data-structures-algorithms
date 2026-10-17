#ifndef DSA_C_INCLUDE_NODE_H
#define DSA_C_INCLUDE_NODE_H

#include "data_t.h"

typedef struct node {
    data_t val;
    struct node* next;
} node;

node* new_node(data_t x);

#endif // DSA_C_INCLUDE_NODE_H