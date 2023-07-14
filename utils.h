#ifndef UTILS_H_
#define UTILS_H_
#include <string.h>

#include "file.h"
#include "string.h"

int verifyStopWord(char* word, char** stopWordsList, int countStopWords);

int binarySearch(String** arr, int left, int right, char* key);

void searchAndPrint(TST* indexTST);

double calculateEndPageRank(TST* pages, double value);

int comparePR(const void* a, const void* b);

double calculateSumInLinks(TST* inLinks, double sum, char* iteracao);

void calculatePageRank(TST* pages, int countPages);

TST* searchAndIndex(TST * indexTST, TST *pages, char *pathPage, String **stopWordsList, int swCount);

TST* indexador(TST* indexTST, Page *page, char *pathPage, String **stopWordsList, int swCount);

void freeArray(void **ptr);

#endif
