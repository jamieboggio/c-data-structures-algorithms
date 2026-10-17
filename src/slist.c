#include "slist.h"
#include "node.h"

slist_t init_slist()
{
    return (slist_t){.n = 0, .head = nullptr, .tail = nullptr};
}

data_t* push_front_slist(slist_t list, data_t* new_element)
{
    if (new_element == nullptr) {
        return nullptr;
    }
    node* u = new_node(*new_element);
    if (u == nullptr) {
        return nullptr;
    }
    u->next = list.head;
    list.head = u;
    if (list.n == 0) {
        list.tail = u;
    }
    list.n++;
    return new_element;
}

data_t* pop_front_slist(slist_t list, data_t* out_element)
{
    if (list.n == 0) {
        return nullptr;
    }
    data_t tmp_val = list.head->val;
    list.head = list.head->next;
    list.n--;
    if (list.n == 0) {
        list.tail = nullptr;
    }
    if (out_element != nullptr) {
        *out_element = tmp_val;
    }
    return out_element;
}

data_t* push_back_slist(slist_t list, data_t* new_element)
{
    if (new_element == nullptr) {
        return nullptr;
    }
    node* u = new_node(*new_element);
    if (u == nullptr) {
        return nullptr;
    }
    list.tail = u;
    if (list.n == 0) {
        list.head = u;
    }
    list.n++;
    return new_element;
}

data_t* pop_back_slist(slist_t list, data_t* out_element)
{
    if (list.n == 0) {
        return nullptr;
    }
    data_t tmp_val = list.tail->val;

    // case n==1
    if (list.n == 1) {
        /* list.head should be equal to list.tail
         * but calling free() on a nullptr is mostly harmless
         */
        free(list.head);
        free(list.tail);
        if (out_element != nullptr) {
            *out_element = tmp_val;
        }
        return out_element;
    }
    // find next to last, and set tail to it
    node* cur_node = list.head;
    while (cur_node->next != list.tail) {
        cur_node = cur_node->next;
    }
    free(list.tail);
    list.tail = cur_node;
    if (out_element != nullptr) {
        *out_element = tmp_val;
    }
    return out_element;
}

data_t* insert_slist(slist_t list, data_t* new_element, size_t index)
{
    if (new_element == nullptr || index > list.n) {
        return nullptr;
    }
    node* u = new_node(*new_element);
    if (u == nullptr) {
        return nullptr;
    }
    node* cur_node = list.head;
    for (size_t i = 1; i < index; i++) {
        cur_node = cur_node->next;
    }
    u->next = cur_node->next;
    cur_node->next = u;
    list.n++;
    return new_element;
}

data_t* erase_slist(slist_t list, data_t* out_element, size_t index)
{
    if (index >= list.n) {
        return nullptr;
    }
    node* cur_node = list.head;
    for (size_t i = 1; i < index; i++) {
        cur_node = cur_node->next;
    }
    if (out_element != nullptr) {
        *out_element = cur_node->next->val;
    }
    node* tmp = cur_node->next;
    cur_node->next = cur_node->next->next;
    free(tmp);
    list.n--;
    return out_element;
}

node* find_slist(slist_t list, data_t wish_element)
{
    node* cur_node = list.head;
    while (cur_node != nullptr) {
        if (cur_node->val == wish_element) {
            return cur_node;
        }
    }
    return nullptr;
}

void reverse_slist(slist_t list)
{
    node* start_head = list.head;
    node* start_tail = list.tail;
    node* prev = nullptr;
    node* curr = start_head;

    while (curr != nullptr) {
        node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list.head = start_tail;
    list.tail = start_head;
}

void free_slist(slist_t list)
{
    node* cur_node = list.head;
    while (cur_node != nullptr) {
        node* tmp = cur_node;
        cur_node = cur_node->next;
        free(tmp);
    }
}