#ifndef RBT_H
#define RBT_H

#include "page.h"
#include "string.h"

typedef struct node RBT;

RBT* create_node(String* key, Page* val, int color);

int is_red(RBT* node);

int getCountValues(RBT* node);

Page** getValues(RBT* node);

RBT* searchRBT(RBT* n, String* key);

void searchValues(RBT* root, char* key);

RBT* rotate_left(RBT* h);

RBT* rotate_right(RBT* h);

void flip_colors(RBT* h);

RBT* RBT_insert(RBT *h, String* key, Page* val);

void printRBT(RBT* node);

#endif