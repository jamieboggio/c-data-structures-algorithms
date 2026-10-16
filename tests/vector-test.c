#include "vector.h"
#include <assert.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static void test_empty_vec(void** state)
{
    (void)state;
    vec_t vec = init_empty_vec();
    assert_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, 0);
}

static void test_init_vec(void** state)
{
    (void)state;

    vec_t vec;
    size_t num_items = 4;
    bool success = init_vec(num_items, &vec);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, num_items);

    free_vec(&vec);
}

static void test_zero_capacity_vec(void** state)
{
    (void)state;

    vec_t vec;
    size_t num_items = 0;
    bool success = init_vec(num_items, &vec);

    assert_true(success);
    assert_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, 0);
}

static void test_too_large_capacity_vec(void** state)
{
    (void)state;

    // intentionally set to true so it fails when it needs to
    // VALGRIND WILL REPORT A "FISHY" VALUE, IGNORE
    // vec_t vec = init_vec(SIZE_MAX / sizeof(data_t), &success);
    vec_t vec;
    size_t theoretical_max = sizeof(data_t) == 1 ? SIZE_MAX : MAX_CAPACITY + 1;
    bool success = init_vec(theoretical_max, &vec);
    assert_false(success);
}

static void test_free_vec(void** state)
{
    (void)state;

    vec_t vec;
    size_t num_items = 32;
    bool success = init_vec(num_items, &vec);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, num_items);

    free_vec(&vec);

    assert_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, 0);
}

static void test_insert_into_existing_capacity(void** state)
{
    (void)state;

    vec_t vec;
    size_t num_items = 32;
    size_t index_of_insert = num_items;
    bool success = init_vec(num_items, &vec);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, num_items);

    assert_true(insert_vec(&vec, index_of_insert, -1));
    assert_int_equal(vec.size, 1);
    assert_int_equal(vec.capacity, 2 * num_items);
    for (size_t i = 0; i < index_of_insert; i++) {
        assert_int_equal(vec.data[i], 0);
    }
    assert_int_equal(vec.data[num_items], -1);

    free_vec(&vec);

    assert_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, 0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_empty_vec),
            cmocka_unit_test(test_init_vec),
            cmocka_unit_test(test_zero_capacity_vec),
            cmocka_unit_test(test_too_large_capacity_vec),
            cmocka_unit_test(test_free_vec),
            cmocka_unit_test(test_insert_into_existing_capacity),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
