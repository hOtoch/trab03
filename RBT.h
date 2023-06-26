#ifndef RBT_H
#define RBT_H

#include "page.h"
#include "string.h"

typedef struct node RBT;

int is_red(RBT* node);

Page** searchRBT(RBT* n, String* key);

RBT* rotate_left(RBT* h);

RBT* rotate_right(RBT* h);

void flip_colors(RBT* h);

#endif