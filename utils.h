#ifndef UTILS_H_
#define UTILS_H_
#include <string.h>

#include "file.h"
#include "string.h"

int verifyStopWord(char* word, char** stopWordsList, int countStopWords);

int binarySearch(String** arr, int left, int right, char* key);

void searchAndPrint(TST* indexTST);

TST* searchAndCalculatePR(TST* pages);

TST* searchAndIndex(TST * indexTST, TST *pages, char *pathPage, String **stopWordsList, int swCount);

TST* calculatePageRank(TST* pages);

TST* indexador(TST* indexTST, Page *page, char *pathPage, String **stopWordsList, int swCount);
#endif
