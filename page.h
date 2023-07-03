#ifndef PAGE_H_
#define PAGE_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string.h"

typedef struct page Page;
Page** createPages(char* path,int countPages);
String* getNome(Page* page);
Page* getPageByName(Page** pages, int countPages, const char* nome);
int getCountLinks(Page* page);
String** getLinks(Page* page);
Page* newPage(char* nome, int countLinks);
Page* getPage(Page** page, int i);
double getPageRank(Page* page);
void setPageRank(Page* page, double pageRank);
void freePage(Page* page);
void freePages(Page** pages, int countPages);


#endif