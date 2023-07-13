#include "TST.h"
#include "page.h"


struct tst {
    void** val;
    int countValues;
    unsigned char c;
    TST *left, *mid, *right;
};

TST* create_node() {
    TST* t = malloc(sizeof(TST));
    t->countValues = 0;
    t->val = NULL;
    t->left = t->mid = t->right = NULL;
    return t;
}



TST* getMid(TST* node){
    if(node == NULL) return NULL;
    return node->mid;
}

TST* getRight(TST* node){
    if(node == NULL) return NULL;
    return node->right;
}

TST* getLeft(TST* node){
    if(node == NULL) return NULL;
    return node->left;
}

void setValues(TST* node, void* val){
    if(node == NULL) return;
    node->val = val;
}

int getCountValues(TST* node){
    if(node == NULL) return 0;
    return node->countValues;
}

void* getValues(TST* node){
    if(node == NULL) return NULL;
    return node->val;
}

void* getFirstElement(TST* node){
    if(node == NULL) return NULL;
    while(getValues(node) == NULL){
        node = getMid(node);
    }

    return getValues(node);
}

TST* rec_insert(TST* t, String* key, void* val, int d) {
    unsigned char c = getString(key)[d];
    if (t == NULL) {
        t = create_node();
        t->c = c;
    }
    
    if (c < t->c) { t->left = rec_insert(t->left, key, val, d); }
    else if (c > t->c) { t->right = rec_insert(t->right, key, val, d); }
    
    else if (d < getSize(key)-1) {
        t->mid = rec_insert(t->mid, key, val, d+1);
    } else { // Inserindo o valor no ultimo nó da palavra     
        t->val = val;
        t->countValues++;
    }
    return t;
}

int searchNGetCountValues(TST* t, String* key){
    t = rec_search(t, key, 0);
    if(t == NULL) return 0;
    return t->countValues;
}

TST* TST_insert(TST* t, String* key , void* val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = getString(key)[d];
    if (c < t->c) { return rec_search(t->left, key, d); }
    else if (c > t->c) { return rec_search(t->right, key, d); }
    else if (d < getSize(key) - 1) {
        return rec_search(t->mid, key, d+1);
    } else { return t; }
}

void* TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) { 
        return NULL;}
    else {
        // for(int i = 0; i < getCountValues(t); i++){
        //     printf("i: %d - %s\n", i, getString(getNome((Page*)t[i].val)));
        // }

        
        return t->val; }
}

void TST_Destroi(TST* t) {
    if (t == NULL) { return; }
    TST_Destroi(t->left);
    TST_Destroi(t->mid);
    TST_Destroi(t->right);
    free(t->val);

    free(t);
}