#include "clist.h"
#include <assert.h>

void init_list(intrusive_list_t *l) {
    intrusive_node_t *head = &(l->head);
    head->prev = head;
    head->next = head;
}

void add_node(intrusive_list_t *l, intrusive_node_t *elem) {
    intrusive_node_t *head = &(l->head);
    intrusive_node_t *first_in_list = head->next;

    first_in_list->prev = elem;

    elem->next = first_in_list;
    elem->prev = head;

    head->next = elem;
}

void remove_node(intrusive_list_t*l, intrusive_node_t *node) {
    assert(l);
    intrusive_node_t *next_node = node->next;
    intrusive_node_t *prev_node = node->prev;
    next_node->prev = prev_node;
    prev_node->next = next_node;
}

int get_length(intrusive_list_t *l) {
    intrusive_node_t *head = &(l->head);
    intrusive_node_t *cur_node = head->next;
    int length = 0;
    while (cur_node != head) {
        length++;
        cur_node = cur_node->next;
    }
    return length;
}

void apply(intrusive_list_t *l, void (*op)(intrusive_node_t *node, void *data), void *data) {
    intrusive_node_t *head = &(l->head);
    intrusive_node_t *cur_node = head->prev;
    
    while (cur_node != head) {
        op(cur_node, data);    
        cur_node = cur_node->prev;
    }
}