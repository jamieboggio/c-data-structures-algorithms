#include "data_t.h"
#include "slist.h"
#include <assert.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * Compare the public list state and its entire node chain.
 * Traverse no more than `count` nodes, so malformed cycles cannot
 * cause the test helper itself to loop forever.
 */
static void assert_slist_equals(const slist_t* list, const data_t* expected,
                                size_t count)
{
    assert_non_null(list);
    assert_int_equal(list->n, count);

    if (count == 0) {
        assert_null(list->head);
        assert_null(list->tail);
        return;
    }

    assert_non_null(list->head);
    assert_non_null(list->tail);

    const node* cur = list->head;
    const node* last = nullptr;
    for (size_t i = 0; i < count; ++i) {
        assert_non_null(cur);
        assert_int_equal(cur->val, expected[i]);
        last = cur;
        cur = cur->next;
    }

    assert_null(cur);
    assert_ptr_equal(last, list->tail);
    assert_null(list->tail->next);
}

static void append_values(slist_t* list, const data_t* values, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        data_t value = values[i];
        assert_ptr_equal(push_back_slist(list, &value), &value);
    }
}

static void test_init_slist(void** state)
{
    (void)state;
    slist_t list = init_slist();
    assert_int_equal(list.n, 0);
    assert_null(list.head);
    assert_null(list.tail);
}

static void test_create_and_free_list(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t list_size = 100;
    for (data_t i = 0; i < list_size; i++) {
        data_t in_val = i;
        data_t* result = push_back_slist(&list, &in_val);
        assert_non_null(result);
        assert_int_equal(i, *result);
    }
    assert_int_equal(list.n, (size_t)list_size);
    node* head = list.head;
    node* tail = list.tail;
    reverse_slist(&list);
    assert_ptr_equal(head, list.tail);
    assert_ptr_equal(tail, list.head);
    {
        node* cur_node = list.head;
        data_t i = list_size - 1;
        while (cur_node != nullptr) {
            data_t curval = cur_node->val;
            assert_int_equal(i, curval);
            i--;
            cur_node = cur_node->next;
        }
    }
    free_slist(&list);
    assert_int_equal(list.n, 0);
    assert_null(list.head);
    assert_null(list.tail);
}

/* Initialization and cleanup */

static void test_free_empty_slist(void** state)
{
    (void)state;
    slist_t list = init_slist();

    free_slist(&list);
    assert_slist_equals(&list, nullptr, 0);

    free_slist(&list); // A second cleanup should also be safe.
    assert_slist_equals(&list, nullptr, 0);
}

/* Push operations */

static void test_push_front_single(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t value = 42;
    const data_t expected[] = {42};

    assert_ptr_equal(push_front_slist(&list, &value), &value);
    assert_slist_equals(&list, expected, 1);
    assert_ptr_equal(list.head, list.tail);

    free_slist(&list);
}

static void test_push_front_order(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t a = 10, b = 20, c = 30;
    const data_t expected[] = {30, 20, 10};

    assert_non_null(push_front_slist(&list, &a));
    assert_non_null(push_front_slist(&list, &b));
    assert_non_null(push_front_slist(&list, &c));
    assert_slist_equals(&list, expected, 3);

    free_slist(&list);
}

static void test_push_back_order(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t expected[] = {10, 20, 30, 40};

    append_values(&list, expected, 4);
    assert_slist_equals(&list, expected, 4);

    free_slist(&list);
}

static void test_push_invalid_arguments(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t value = 7;

    assert_null(push_front_slist(nullptr, &value));
    assert_null(push_back_slist(nullptr, &value));
    assert_null(push_front_slist(&list, nullptr));
    assert_null(push_back_slist(&list, nullptr));
    assert_slist_equals(&list, nullptr, 0);

    free_slist(&list);
}

/* Pop operations */

static void test_pop_front_empty(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t out = -1;

    assert_null(pop_front_slist(&list, &out));
    assert_int_equal(out, -1);
    assert_slist_equals(&list, nullptr, 0);
}

static void test_pop_front_multiple(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t values[] = {5, 6, 7};
    const data_t after_one[] = {6, 7};
    const data_t after_two[] = {7};
    data_t out = -1;

    append_values(&list, values, 3);

    assert_ptr_equal(pop_front_slist(&list, &out), &out);
    assert_int_equal(out, 5);
    assert_slist_equals(&list, after_one, 2);

    assert_ptr_equal(pop_front_slist(&list, &out), &out);
    assert_int_equal(out, 6);
    assert_slist_equals(&list, after_two, 1);

    assert_ptr_equal(pop_front_slist(&list, &out), &out);
    assert_int_equal(out, 7);
    assert_slist_equals(&list, nullptr, 0);

    free_slist(&list);
}

static void test_pop_back_empty(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t out = -1;

    assert_null(pop_back_slist(&list, &out));
    assert_int_equal(out, -1);
    assert_slist_equals(&list, nullptr, 0);
}

static void test_pop_back_single(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t value = 123, out = -1;

    assert_non_null(push_back_slist(&list, &value));
    assert_ptr_equal(pop_back_slist(&list, &out), &out);
    assert_int_equal(out, 123);
    assert_slist_equals(&list, nullptr, 0);

    free_slist(&list);
}

static void test_pop_back_multiple(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t values[] = {1, 2, 3};
    const data_t expected[] = {1, 2};
    data_t out = -1;

    append_values(&list, values, 3);

    assert_ptr_equal(pop_back_slist(&list, &out), &out);
    assert_int_equal(out, 3);
    assert_slist_equals(&list, expected, 2);

    free_slist(&list);
}

/* Indexed insertion */

static void test_insert_front(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {20, 30};
    const data_t expected[] = {10, 20, 30};
    data_t value = 10;

    append_values(&list, original, 2);
    assert_ptr_equal(insert_slist(&list, &value, 0), &value);
    assert_slist_equals(&list, expected, 3);

    free_slist(&list);
}

static void test_insert_middle(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {10, 30};
    const data_t expected[] = {10, 20, 30};
    data_t value = 20;

    append_values(&list, original, 2);
    assert_ptr_equal(insert_slist(&list, &value, 1), &value);
    assert_slist_equals(&list, expected, 3);

    free_slist(&list);
}

static void test_insert_end(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {10, 20};
    const data_t expected[] = {10, 20, 30};
    data_t value = 30;

    append_values(&list, original, 2);
    assert_ptr_equal(insert_slist(&list, &value, list.n), &value);
    assert_slist_equals(&list, expected, 3);

    free_slist(&list);
}

static void test_insert_empty(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t expected[] = {55};
    data_t value = 55;

    assert_ptr_equal(insert_slist(&list, &value, 0), &value);
    assert_slist_equals(&list, expected, 1);

    free_slist(&list);
}

static void test_insert_invalid_index(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {10, 20};
    data_t value = 99;

    append_values(&list, original, 2);
    assert_null(insert_slist(&list, &value, 3));
    assert_slist_equals(&list, original, 2);

    free_slist(&list);
}

/* Indexed erasure */

static void test_erase_front(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {10, 20, 30};
    const data_t expected[] = {20, 30};
    data_t out = -1;

    append_values(&list, original, 3);
    assert_ptr_equal(erase_slist(&list, &out, 0), &out);
    assert_int_equal(out, 10);
    assert_slist_equals(&list, expected, 2);

    free_slist(&list);
}

static void test_erase_middle(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {10, 20, 30};
    const data_t expected[] = {10, 30};
    data_t out = -1;

    append_values(&list, original, 3);
    assert_ptr_equal(erase_slist(&list, &out, 1), &out);
    assert_int_equal(out, 20);
    assert_slist_equals(&list, expected, 2);

    free_slist(&list);
}

static void test_erase_last(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {10, 20, 30};
    const data_t expected[] = {10, 20};
    data_t out = -1;

    append_values(&list, original, 3);
    assert_ptr_equal(erase_slist(&list, &out, 2), &out);
    assert_int_equal(out, 30);
    assert_slist_equals(&list, expected, 2);

    free_slist(&list);
}

static void test_erase_only_element(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t value = 42, out = -1;

    assert_non_null(push_front_slist(&list, &value));
    assert_ptr_equal(erase_slist(&list, &out, 0), &out);
    assert_int_equal(out, 42);
    assert_slist_equals(&list, nullptr, 0);

    free_slist(&list);
}

static void test_erase_invalid_index(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t original[] = {10, 20};
    data_t out = -1;

    append_values(&list, original, 2);
    assert_null(erase_slist(&list, &out, 2));
    assert_int_equal(out, -1);
    assert_slist_equals(&list, original, 2);

    free_slist(&list);
}

/* Search and read operations */

static void test_find_first_match(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t values[] = {7, 9, 7};

    append_values(&list, values, 3);
    assert_ptr_equal(find_slist(&list, 7), list.head);

    free_slist(&list);
}

static void test_find_middle_and_missing(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t values[] = {7, 9, 11};

    append_values(&list, values, 3);
    node* found = find_slist(&list, 9);
    assert_non_null(found);
    assert_int_equal(found->val, 9);
    assert_null(find_slist(&list, 42));

    free_slist(&list);
}

static void test_peek_front(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t out = -1;
    const data_t values[] = {12, 34};

    assert_null(peek_front_slist(&list, &out));
    assert_int_equal(out, -1);

    append_values(&list, values, 2);
    assert_ptr_equal(peek_front_slist(&list, &out), &out);
    assert_int_equal(out, 12);
    assert_slist_equals(&list, values, 2);

    free_slist(&list);
}

/* Reversal */

static void test_reverse_empty_and_single(void** state)
{
    (void)state;
    slist_t list = init_slist();
    data_t value = 88;
    const data_t expected[] = {88};

    reverse_slist(&list);
    assert_slist_equals(&list, nullptr, 0);

    assert_non_null(push_front_slist(&list, &value));
    reverse_slist(&list);
    assert_slist_equals(&list, expected, 1);

    free_slist(&list);
}

static void test_reverse_twice(void** state)
{
    (void)state;
    slist_t list = init_slist();
    const data_t values[] = {1, 2, 3, 4};
    const data_t reversed[] = {4, 3, 2, 1};

    append_values(&list, values, 4);
    reverse_slist(&list);
    assert_slist_equals(&list, reversed, 4);

    reverse_slist(&list);
    assert_slist_equals(&list, values, 4);

    free_slist(&list);
}

/* Defensive argument checks */

static void test_null_list_arguments(void** state)
{
    (void)state;
    data_t value = 1;

    assert_null(pop_front_slist(nullptr, &value));
    assert_null(pop_back_slist(nullptr, &value));
    assert_null(insert_slist(nullptr, &value, 0));
    assert_null(erase_slist(nullptr, &value, 0));
    assert_null(find_slist(nullptr, value));
    assert_null(peek_front_slist(nullptr, &value));
    reverse_slist(nullptr);
    free_slist(nullptr);
}

int main(void)
{
    // FUTURE JAMIE
    // PLEASE DO NOT FORGET TO FREE YOUR DATA STRUCTURES!
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_and_free_list),
        cmocka_unit_test(test_init_slist),
        cmocka_unit_test(test_free_empty_slist),
        cmocka_unit_test(test_push_front_single),
        cmocka_unit_test(test_push_front_order),
        cmocka_unit_test(test_push_back_order),
        cmocka_unit_test(test_push_invalid_arguments),
        cmocka_unit_test(test_pop_front_empty),
        cmocka_unit_test(test_pop_front_multiple),
        cmocka_unit_test(test_pop_back_empty),
        cmocka_unit_test(test_pop_back_single),
        cmocka_unit_test(test_pop_back_multiple),
        cmocka_unit_test(test_insert_front),
        cmocka_unit_test(test_insert_middle),
        cmocka_unit_test(test_insert_end),
        cmocka_unit_test(test_insert_empty),
        cmocka_unit_test(test_insert_invalid_index),
        cmocka_unit_test(test_erase_front),
        cmocka_unit_test(test_erase_middle),
        cmocka_unit_test(test_erase_last),
        cmocka_unit_test(test_erase_only_element),
        cmocka_unit_test(test_erase_invalid_index),
        cmocka_unit_test(test_find_first_match),
        cmocka_unit_test(test_find_middle_and_missing),
        cmocka_unit_test(test_peek_front),
        cmocka_unit_test(test_reverse_empty_and_single),
        cmocka_unit_test(test_reverse_twice),
        cmocka_unit_test(test_null_list_arguments),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
