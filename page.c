#include "page.h"
#include "string.h"
#include "utils.h"


struct page {
    String* nome;
    int countInLinks;
    int countOutLinks;
    double pageRank;
    TST* links;
};

// void calculatePageRank(TST* pages, String** namePages, int countPages){
//     int firstIteration = 1;
//     double alfa = 0.85;

//     while(1){
//         if(firstIteration){
//             for(int i = 0; i < countPages; i++){
            
//             }
//         }
//     }
        
// }



String* getNome(Page* page){
    return page->nome;
}

TST* getLinks(Page* page){
    return page->links;
}

void setLinks(Page* page, TST* links){
    page->links = links;
}

int getCountOutLinks(Page* page){
    return page->countOutLinks;
}

int getCountInLinks(Page* page){
    return page->countInLinks;
}

void setCountOutLinks(Page* page, int countOutLinks){
    page->countOutLinks = countOutLinks;
}

void setCountInLinks(Page* page, int countInLinks){
    page->countInLinks = countInLinks;
}

Page* getPage(Page** page, int i){
    return page[i];
}

double getPageRank(Page* page){
    return page->pageRank;
}

void setPageRank(Page* page, double pageRank){
    page->pageRank = pageRank;
}

Page* newPage(char* nome, int countLinks){
    Page* page = (Page*)malloc(sizeof(Page));
    page->nome = createString(nome);
    page->links = NULL;
    page->pageRank = 0;
    page->countInLinks = 0;
    page->countOutLinks = countLinks;
    return page;
}

void freePages(Page** pages, int countPages){
    for(int i = 0; i < countPages; i++){
        freePage(pages[i]);
    }
    free(pages);
}

void freePage(Page* page){
    free(page->nome);
    free(page);
}

