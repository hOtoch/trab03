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

int getCountValues(TST* node){
    if(node == NULL) return 0;
    return node->countValues;
}

void* getValues(TST* node){
    if(node == NULL) return NULL;
    return node->val;
}

void* searchAndGetValue(TST* root, void* val){
    if(root == NULL) return NULL;
    if(root->val != NULL) return root->val;

    val = searchAndGetValue(root->left, val);
    val = searchAndGetValue(root->mid, val);
    val = searchAndGetValue(root->right, val);

    return val;
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
        
        if(t->countValues == 0){
            t->val = (void**)TST_insert((TST*)t->val, key,val);
            t->countValues = 1;
        }else{
            void* result = TST_search((TST*)t->val, key);

            if(result == NULL){
                t->val = (void**)TST_insert((TST*)t->val, key,val);
                t->countValues++;
            }else{
                return t;
            }
        }



        // if(t->countValues == 0){
        //     // printf("CRIANDO VETOR DE VALUE\n");
        //     t->val = malloc(sizeof(void*));
        //     t->val[0] = val;
        //     t->countValues = 1;
        // }else{
        //     if(compare(getNome((Page*)t->val[t->countValues-1]), getNome((Page*)val)) == 0){
        //         // printf("VALOR JA EXISTE\n");
        //         return t;
        //     } 
            
        //     t->countValues++;
        //     t->val = realloc(t->val, sizeof(void*)*t->countValues);
        //     t->val[t->countValues - 1] = val;
            
        // }
        
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
        //     printf("i: %d - %s\n", i, getString(getNome(pages[i])));
        // }

        
        return t->val; }
}

