#ifndef PAGE_H_
#define PAGE_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string.h"
#include "TST.h"

typedef struct page Page;
String* getNome(Page* page);
Page* getPageByName(Page** pages, int countPages, const char* nome);
int getCountInLinks(Page* page);
int getCountOutLinks(Page* page);
TST* getLinks(Page* page);
void setLinks(Page* page, TST* links);
void setCountOutLinks(Page* page, int countOutLinks);
void setCountInLinks(Page* page, int countInLinks);
Page* newPage(char* nome, int countLinks);
Page* getPage(Page** page, int i);
double getOldPageRank(Page* page);
void setOldPageRank(Page* page, double oldPageRank);
double getPageRank(Page* page);
void setPageRank(Page* page, double pageRank);
void freePage(Page* page);
void freeArrayPage(Page** pages, int countPages);
void freePagesTST(void* t);
Page** TST_intersecao(TST* guia, TST* segunda, Page** resultTST, int* indice);

#endif