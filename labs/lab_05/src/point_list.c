#include "point_list.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

void add_point(intrusive_list_t *l, int x, int y) {
    point_t *p = malloc(sizeof(point_t));
    assert(p);
    p->x = x;
    p->y = y;
    add_node(l, &(p->node));
}

void erase_point(intrusive_list_t *l, point_t *p) {
    remove_node(l, &(p->node));
    free(p);
}

void remove_point(intrusive_list_t *l, int x, int y) { 
    intrusive_node_t *head = &(l->head);
    intrusive_node_t *cur_node = head->next;
    
    while (cur_node != head) {
        intrusive_node_t *next_node = cur_node->next;
        
        point_t *item = container_of(cur_node, point_t, node);
        if (item->x == x && item->y == y) 
            erase_point(l, item);
        
        cur_node = next_node;
    }
}

void remove_all_points(intrusive_list_t *l) {
    intrusive_node_t *head = &(l->head);

    while (head->next != head) 
        erase_point(l, container_of(head->next, point_t, node));
}

void show_all_points(intrusive_list_t *l) {
    intrusive_node_t *head = &(l->head);
    intrusive_node_t *cur_node = head->next;
    
    while (cur_node != head) {
        if (cur_node != head->next)
            printf(" ");

        point_t *item = container_of(cur_node, point_t, node);
        printf("(%d %d)", item->x, item->y);
        
        cur_node = cur_node->next;
    }
    printf("\n");
}