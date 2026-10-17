
#include "data_t.h"
#include "slist.h"
#include <assert.h>
#include <cmocka.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
    assert_int_equal(list.n, list_size);
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

int main(void)
{
    // FUTURE JAMIE
    // PLEASE DO NOT FORGET TO FREE YOUR DATA STRUCTURES!
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_create_and_free_list),
                                       cmocka_unit_test(test_init_slist)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}
