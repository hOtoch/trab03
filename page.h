#ifndef PAGE_H_
#define PAGE_H_
#include <stdio.h>
#include <stdlib.h>


typedef struct page Page;
Page* newPage(char* nome, int countLinks, Page** links);
void freePage(Page* page);


#endif