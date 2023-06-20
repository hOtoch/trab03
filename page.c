#include "page.h"

struct page {
    char* nome;
    int countLinks;
    Page** links;
};

Page* newPage(char* nome, int countLinks, Page** links){
    Page* page = (Page*)malloc(sizeof(Page));
    page->nome = nome;
    page->countLinks = countLinks;
    page->links = links;
    return page;
}

void freePage(Page* page){
    free(page->nome);
    free(page->links);
    free(page);
}

