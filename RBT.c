#include "RBT.h"


struct node{
    String* key;
    Page** pages;
    int color; // 1 --> RED, 0 --> BLACK
    struct node* left;
    struct node* right;
};

int is_red(RBT* node){
    if(node == NULL) return 0;
    return node->color == 1;
}


Page** searchRBT(RBT* n, String* key){
    if(n == NULL) return NULL;
    int cmp = compare(key, n->key);
    if(cmp == 0) return n->pages;
    else if(cmp < 0) return searchRBT(n->left, key);
    else return searchRBT(n->right, key);
}

RBT* rotate_left(RBT* h){
    RBT* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = x->left->color;
    x->left->color = 1;
    return x;
}

RBT* rotate_right(RBT* h){
    RBT* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = x->right->color;
    x->right->color = 1;
    return x;
}

void flip_colors(RBT* h){
    h->color = 1;
    h->left->color = 0;
    h->right->color = 0;
}