#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "clist.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
  int x, y;
  struct intrusive_node node;
} point_t;

void add_point(intrusive_list_t *l, int x, int y) {
    point_t *p = malloc(sizeof(point_t));
    assert(p);
    p -> x = x;
    p -> y = y;
    add_node(l, &(p -> node));
}

void erase_point(intrusive_list_t *l, point_t *p) {
    remove_node(l, &(p -> node));
    free(p);
}

void remove_point(intrusive_list_t *l, int x, int y) { 
    intrusive_node_t *head = &(l -> head);
    intrusive_node_t *cur_node = head -> next;
    
    while (cur_node != head) {
        intrusive_node_t *next_node = cur_node -> next;
        
        point_t *item = container_of(cur_node, point_t, node);
        if (item -> x == x && item -> y == y) 
            erase_point(l, item);
        
        cur_node = next_node;
    }
}

void remove_all_points(intrusive_list_t *l) {
    intrusive_node_t *head = &(l -> head);

    while (head -> next != head) 
        erase_point(l, container_of(head -> next, point_t, node));
}

void show_all_points(intrusive_list_t *l) {
    intrusive_node_t *head = &(l -> head);
    intrusive_node_t *cur_node = head -> next;
    
    while (cur_node != head) {
        if (cur_node != head -> next)
            printf(" ");

        point_t *item = container_of(cur_node, point_t, node);
        printf("(%d %d)", item -> x, item -> y);
        
        cur_node = cur_node -> next;
    }
    printf("\n");
}

int main() {
    intrusive_list_t list;
    intrusive_list_t *l = &list;
    init_list(l);

    char *cmd = malloc(10 * sizeof(char));
    assert(cmd);

    while (scanf("%10s", cmd)) {
        if (strcmp(cmd, "add") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            add_point(l, x, y);
        }
        else if (strcmp(cmd, "rm") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            remove_point(l, x, y);
        }
        else if (strcmp(cmd, "print") == 0) 
            show_all_points(l);
        else if (strcmp(cmd, "rma") == 0)
            remove_all_points(l);
        else if (strcmp(cmd, "len") == 0)
            printf("%d\n", get_length(l));
        else if (strcmp(cmd, "exit") == 0)
            break;
        else
            printf("Unknown command\n");
    }
    
    remove_all_points(l);
    free(cmd);
}