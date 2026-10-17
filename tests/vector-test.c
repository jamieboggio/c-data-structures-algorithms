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

    (void)state;
    vec_t vec;
    (void)init_vec(&vec, 4);
    size_t magic_max = 2;
    for (data_t i = 0; i < magic_max; i++) {
        push_back_vec(&vec, i + 1);
    }
    assert_int_equal(vec.capacity, 4);
    assert_int_equal(vec.size, 2);
    assert_true(resize_vec(&vec, 100));

    assert_int_equal(vec.capacity, 200);
    assert_int_equal(vec.size, 100);

    free_vec(&vec);
}

static void test_set_vec(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    assert_true(init_vec(&vec, 4));

    assert_true(push_back_vec(&vec, 10));
    assert_true(push_back_vec(&vec, 20));
    assert_true(push_back_vec(&vec, 30));

    assert_true(set_vec(&vec, 1, 99));
    assert_int_equal(vec.data[0], 10);
    assert_int_equal(vec.data[1], 99);
    assert_int_equal(vec.data[2], 30);
    assert_int_equal(vec.size, 3);

    assert_false(set_vec(&vec, 3, 100));
    assert_false(set_vec(nullptr, 0, 100));

    free_vec(&vec);
}

static void test_get_vec(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    data_t result = -1;

    assert_false(get_vec(vec, 0, &result));
    assert_int_equal(result, -1);

    assert_true(push_back_vec(&vec, 42));
    assert_true(push_back_vec(&vec, 69));

    assert_true(get_vec(vec, 0, &result));
    assert_int_equal(result, 42);

    assert_true(get_vec(vec, 1, &result));
    assert_int_equal(result, 69);

    assert_false(get_vec(vec, 2, &result));
    assert_int_equal(result, 69);

    assert_false(get_vec(vec, 0, nullptr));

    free_vec(&vec);
}

static void test_reserve_vec(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    assert_true(init_vec(&vec, 4));

    assert_true(push_back_vec(&vec, 10));
    assert_true(push_back_vec(&vec, 20));

    assert_true(reserve_vec(&vec, 16));
    assert_int_equal(vec.capacity, 16);
    assert_int_equal(vec.size, 2);
    assert_int_equal(vec.data[0], 10);
    assert_int_equal(vec.data[1], 20);

    assert_true(reserve_vec(&vec, 8));
    assert_int_equal(vec.capacity, 16);

    assert_true(reserve_vec(&vec, 16));
    assert_int_equal(vec.capacity, 16);

    free_vec(&vec);
}

static void test_reserve_null_vec(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();

    assert_true(reserve_vec(&vec, 8));
    assert_int_equal(vec.size, 0);
    assert_true(vec.capacity >= 8);
    assert_non_null(vec.data);

    assert_true(push_back_vec(&vec, 123));
    assert_int_equal(vec.size, 1);
    assert_int_equal(vec.data[0], 123);

    free_vec(&vec);
}

static void test_resize_growth_and_shrink(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    assert_true(init_vec(&vec, 4));

    assert_true(push_back_vec(&vec, 10));
    assert_true(push_back_vec(&vec, 20));

    assert_true(resize_vec(&vec, 10));
    assert_int_equal(vec.size, 10);
    assert_true(vec.capacity >= 10);

    assert_int_equal(vec.data[0], 10);
    assert_int_equal(vec.data[1], 20);

    for (size_t i = 2; i < 10; i++) {
        assert_int_equal(vec.data[i], 0);
    }

    assert_true(resize_vec(&vec, 1));
    assert_int_equal(vec.size, 1);
    assert_int_equal(vec.data[0], 10);

    assert_true(resize_vec(&vec, 5));
    assert_int_equal(vec.size, 5);

    for (size_t i = 1; i < 5; i++) {
        assert_int_equal(vec.data[i], 0);
    }

    assert_true(resize_vec(&vec, 0));
    assert_int_equal(vec.size, 0);

    free_vec(&vec);
}

static void test_insert_into_preallocated_empty_vec(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    assert_true(init_vec(&vec, 8));

    data_t* original_data = vec.data;
    size_t original_capacity = vec.capacity;

    assert_true(insert_vec(&vec, 0, 42));

    assert_int_equal(vec.size, 1);
    assert_int_equal(vec.capacity, original_capacity);
    assert_ptr_equal(vec.data, original_data);
    assert_int_equal(vec.data[0], 42);

    free_vec(&vec);
}

static void test_insert_at_front(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    assert_true(init_vec(&vec, 8));

    assert_true(push_back_vec(&vec, 10));
    assert_true(push_back_vec(&vec, 20));
    assert_true(push_back_vec(&vec, 30));

    assert_true(insert_vec(&vec, 0, 99));

    assert_int_equal(vec.size, 4);
    assert_int_equal(vec.data[0], 99);
    assert_int_equal(vec.data[1], 10);
    assert_int_equal(vec.data[2], 20);
    assert_int_equal(vec.data[3], 30);

    free_vec(&vec);
}

static void test_insert_at_back(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    assert_true(init_vec(&vec, 7));

    const data_t in_array[] = {8, 6, 7, 5, 3, 0, 9};
    const size_t in_size = sizeof(in_array) / sizeof(in_array[0]);

    for (size_t i = 0; i < in_size; i++) {
        assert_true(push_back_vec(&vec, in_array[i]));
    }

    assert_true(insert_vec(&vec, in_size, 99));

    const data_t out_array[] = {8, 6, 7, 5, 3, 0, 9, 99};
    const size_t out_size = sizeof(out_array) / sizeof(out_array[0]);
    assert_int_equal(vec.size, out_size);
    assert_int_equal(vec.capacity, 2 * in_size);
    for (size_t i = 0; i < out_size; i++) {
        data_t val;
        assert_true(get_vec(vec, i, &val));
        assert_int_equal(val, out_array[i]);
    }

    free_vec(&vec);
}

static void test_insert_invalid_index(void** state)
{
    (void)state;

    vec_t vec = init_null_vec();
    assert_true(init_vec(&vec, 7));

    const data_t in_array[] = {8, 6, 7, 5, 3, 0, 9};
    const size_t in_size = sizeof(in_array) / sizeof(in_array[0]);

    for (size_t i = 0; i < in_size; i++) {
        assert_true(push_back_vec(&vec, in_array[i]));
    }

    assert_false(insert_vec(&vec, in_size + 1, 99));

    const data_t out_array[] = {8, 6, 7, 5, 3, 0, 9};
    const size_t out_size = sizeof(out_array) / sizeof(out_array[0]);
    assert_int_equal(vec.size, out_size);
    assert_int_equal(vec.capacity, in_size);
    for (size_t i = 0; i < out_size; i++) {
        data_t val;
        assert_true(get_vec(vec, i, &val));
        assert_int_equal(val, out_array[i]);
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
                                       cmocka_unit_test(test_pop_back_vec),
                                       cmocka_unit_test(test_insert_vec),
                                       cmocka_unit_test(test_erase_vec),
                                       cmocka_unit_test(test_resize_vec),
                                       cmocka_unit_test(test_set_vec),
                                       cmocka_unit_test(test_get_vec),
                                       cmocka_unit_test(test_reserve_vec),
                                       cmocka_unit_test(test_reserve_null_vec),
                                       cmocka_unit_test(test_resize_growth_and_shrink),
                                       cmocka_unit_test(test_insert_into_preallocated_empty_vec),
                                       cmocka_unit_test(test_insert_at_front),
                                       cmocka_unit_test(test_insert_at_back),
                                       cmocka_unit_test(test_insert_invalid_index)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}
