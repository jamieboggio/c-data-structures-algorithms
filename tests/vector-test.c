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
    bool success = init_vec(&vec, num_items);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, num_items);

    free_vec(&vec);
}

static void test_init_vec_zero_capacity(void** state)
{
    (void)state;

    vec_t vec;
    size_t num_items = 0;
    bool success = init_vec(&vec, num_items);

    assert_true(success);
    assert_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, 0);
}

static void test_init_vec_too_large_capacity(void** state)
{
    (void)state;

    // intentionally set to true so it fails when it needs to
    // VALGRIND WILL REPORT A "FISHY" VALUE, IGNORE
    vec_t vec;
    size_t theoretical_max = sizeof(data_t) == 1 ? SIZE_MAX : MAX_CAPACITY + 1;
    bool success = init_vec(&vec, theoretical_max);
    assert_false(success);
}

static void test_init_vec_large_capacity(void** state)
{
    (void)state;

    vec_t vec;
    const size_t large_num = 1'000'000'000;
    bool success = init_vec(&vec, large_num);
    assert_true(success);

    free_vec(&vec);
}

static void test_free_vec(void** state)
{
    (void)state;

    vec_t vec;
    size_t num_items = 32;
    bool success = init_vec(&vec, num_items);

    assert_true(success);
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, num_items);

    free_vec(&vec);

    assert_null(vec.data);
    assert_int_equal(vec.size, 0);
    assert_int_equal(vec.capacity, 0);
}

static void test_push_back_vec(void** state)
{
    (void)state;
    vec_t vec = init_empty_vec();
    data_t element = 0x69420;
    assert_true(push_back_vec(&vec, element));
    assert_non_null(vec.data);
    assert_int_equal(vec.size, 1);
    assert_int_equal(vec.capacity, DEFAULT_CAPACITY);
    assert_int_equal(vec.data[0], element);

    free_vec(&vec);
}

static void test_pop_back_vec(void** state)
{
    (void)state;
    vec_t vec = init_empty_vec();
    for (data_t i = 0; i < 69; i++) {
        push_back_vec(&vec, i + 1);
    }
    for (data_t i = 68; i >= 0; i--) {
        data_t old_element;
        assert_true(pop_back_element(&vec, &old_element));
        assert_int_equal(i + 1, old_element);
    }

    free_vec(&vec);
}

int main(void)
{
    // FUTURE JAMIE
    // PLEASE DO NOT FORGET TO FREE YOUR VECTORS!
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_empty_vec),
                                       cmocka_unit_test(test_init_vec),
                                       cmocka_unit_test(test_init_vec_zero_capacity),
                                       cmocka_unit_test(test_init_vec_too_large_capacity),
                                       cmocka_unit_test(test_init_vec_large_capacity),
                                       cmocka_unit_test(test_free_vec),
                                       cmocka_unit_test(test_push_back_vec),
                                       cmocka_unit_test(test_pop_back_vec)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}
