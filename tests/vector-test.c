#include "vector.h"
#include <assert.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stddef.h>

static void test_empty_vec(void** state)
{
    (void)state;
    vec_t vec = init_empty_vec();
    assert_null(vec.data);
    assert_int_equal(vec.len, 0);
    assert_int_equal(vec.capacity, 0);
}

static void test_init_vec(void** state)
{
    (void)state;

    bool success = false;
    vec_t vec = init_vec(4, &success);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.len, 0);
    assert_int_equal(vec.capacity, 4);

    free_vec(&vec);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_empty_vec),
            cmocka_unit_test(test_init_vec),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
