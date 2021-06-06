#ifndef CLIST_H_
#define CLIST_H_

typedef struct intrusive_node {
  struct intrusive_node *next;
  struct intrusive_node *prev;
} intrusive_node_t;

typedef struct intrusive_list {
  struct intrusive_node head;
} intrusive_list_t;

void init_list(intrusive_list_t *l);
void add_node(intrusive_list_t *l, intrusive_node_t *elem);
void remove_node(intrusive_list_t *l, intrusive_node_t *elem);
int get_length(intrusive_list_t *l);
void apply(intrusive_list_t *l, void (*op)(intrusive_node_t *node, void *data), void *data);

#endif