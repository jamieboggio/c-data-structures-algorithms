#include "vector.h"
#include <assert.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static void test_empty_vec(void** state)
{
    (void)state;
    vec_t vec = init_null_vec();
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
    vec_t vec = init_null_vec();
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
    vec_t vec = init_null_vec();
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

static void test_insert_vec(void** state)
{
    (void)state;
    vec_t vec = init_null_vec();
    size_t magic_max = 69;
    for (data_t i = 0; i < magic_max; i++) {
        push_back_vec(&vec, i + 1);
    }
    size_t magic_index = 52;
    data_t magic_num = 0x69420;
    assert_true(insert_vec(&vec, magic_index, magic_num));
    for (data_t i = 0; i < magic_index; i++) {
        assert_int_equal(vec.data[i], i + 1);
    }
    assert_int_equal(vec.data[magic_index], magic_num);
    for (data_t i = magic_index + 1; i <= magic_max; i++) {
        assert_int_equal(vec.data[i], i);
    }

    free_vec(&vec);
}

void test_erase_vec(void** state)
{
    (void)state;
    vec_t vec = init_null_vec();
    size_t magic_max = 69;
    for (data_t i = 0; i < magic_max; i++) {
        push_back_vec(&vec, i + 1);
    }
    size_t magic_index = 52;
    data_t magic_num = 0x69420;
    insert_vec(&vec, magic_index, magic_num);

    data_t out_val;
    assert_true(erase_vec(&vec, magic_index, &out_val));
    assert_int_equal(magic_num, out_val);

    free_vec(&vec);
}

void test_resize_vec(void** state)
{
}

void test_set_vec(void** state)
{
}

void test_get_vec(void** state)
{
}

void test_reserve_vec(void** state)
{
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
                                       cmocka_unit_test(test_pop_back_vec),
                                       cmocka_unit_test(test_insert_vec),
                                       cmocka_unit_test(test_erase_vec)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}
