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

    bool success = false;
    size_t num_items = 4;
    vec_t vec = init_vec(num_items, &success);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, num_items);

    free_vec(&vec);
}

static void test_zero_capacity_vec(void** state)
{
    (void)state;

    bool success = false;
    vec_t vec = init_vec(0, &success);

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
    bool success = true;
    vec_t vec = init_vec(SIZE_MAX / sizeof(data_t), &success);
    assert_false(success);
}

static void test_free_vec(void** state)
{
    (void)state;

    bool success = false;
    size_t num_items = 32;
    vec_t vec = init_vec(num_items, &success);

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

    bool success = false;
    size_t num_items = 32;
    vec_t vec = init_vec(num_items, &success);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, num_items);

    assert_true(insert_vec(&vec, num_items, -1));
    assert_int_equal(vec.size, 1);
    assert_int_equal(vec.capacity, 2 * num_items);
    for (size_t i = 0; i < num_items; i++) {
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
