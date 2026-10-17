#include "node.h"
#include <stdlib.h>

node* new_node(data_t x)
{
    node n = {.val = x, .next = nullptr};
    node* new_data = (node*)malloc(sizeof(node));
    if (new_data != nullptr) {
        *new_data = n;
    }
    return new_data;
}