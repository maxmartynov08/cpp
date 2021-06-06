#ifndef POINT_LIST_H_
#define POINT_LIST_H_

#include "clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

typedef struct point {
  int x, y;
  struct intrusive_node node;
} point_t;

void add_point(intrusive_list_t *l, int x, int y);

void remove_point(intrusive_list_t *l, int x, int y);

void remove_all_points(intrusive_list_t *l);

void show_all_points(intrusive_list_t *l);

#endif