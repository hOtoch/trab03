#ifndef UTILS_H_
#define UTILS_H_
#include <string.h>

#include "file.h"
#include "string.h"

int verifyStopWord(char* word, char** stopWordsList, int countStopWords);

void removeNewLine(char* str);

int binarySearch(String** arr, int left, int right, char* key);
   

#endif
