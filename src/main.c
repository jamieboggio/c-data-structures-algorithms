#include "vector.h"
#include <stdio.h>

int main(void)
{
    vec_t vec;
    if (!init_empty_vec(&vec)) {
        return 1;
    }
    for (data_t i = 0; i < 100; i++) {
        (void)push_back_vec(&vec, (2 * i) + 1);
    }
    print_vec(vec);
    return 0;
}
