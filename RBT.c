#include "RBT.h"


struct node{
    String* key;
    Page** value;
    int countValues;
    int color; // 1 --> RED, 0 --> BLACK
    struct node* left;
    struct node* right;
};

RBT* create_node(String* key, Page* val,int color){
    RBT* node = (RBT*) malloc(sizeof(RBT));
    node->key = key;
    node->countValues = 0;
    node->value[0] = val;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    return node;
}



int is_red(RBT* node){
    if(node == NULL) return 0;
    return node->color == 1;
}


Page** searchRBT(RBT* n, String* key){
    if(n == NULL) return NULL;
    int cmp = compare(key, n->key);
    if(cmp == 0) return n->value;
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

RBT* RBT_insert(RBT *h, String* key, Page* val) {
    // Insert at bottom and color it red.
    // printf("Termo %s entrou na arvore\n", getString(key));
    if (h == NULL) {
        printf("criando nó %s\n", getString(key));
        return create_node(key, val, 1);
    }
    int cmp = compare(key, h->key);
    // printf("comparando %s com %s\n : %d\n", getString(key), getString(h->key), cmp);

    if (cmp < 0) {
        // printf("inserindo o termo %s a esquerda\n", getString(key));
        h->left = RBT_insert(h->left, key, val);
    }

    else if (cmp > 0) {
        // printf("inserindo o termo %s a direita\n", getString(key));
        h->right = RBT_insert(h->right, key, val);
    }

    else /*cmp == 0*/ {
        // printf("Termo %s ja existe\n", getString(key));
        h->value[h->countValues] = val;
        h->countValues++;
    }
    // Lean left.
    if (is_red(h->right) && !is_red(h->left)) { h = rotate_left(h); }
    // Balance 4-node.
    if (is_red(h->left) && is_red(h->left->left)) { h = rotate_right(h); }
    // Split 4-node.
    if (is_red(h->left) && is_red(h->right)) { flip_colors(h); }

    // printf("Termo %s saiu da arvore\n", getString(key));
    return h;
}

void printRBT(RBT* node) {
    if (node == NULL) return;

    printRBT(node->left);

    printf("%s : ", getString(node->key));
    for (int i = 0; i < node->countValues; i++) {
        printf("%s", getNome(node->value[i]));
        if (i < node->countValues - 1) {
            printf(", ");
        }
    }
    printf("\n");

    printRBT(node->right);
}
