#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>

typedef struct string String;

String* createString(char* str);

void toLowerCase(String* str);

void removeNewLine(String* str);

int setSize(String* str, int size);

int compare_from(String *s, String *t, int d);

int compareQs(const void* a, const void* b);

int compare(String *s, String *t);

char* getString(String* string);

int getSize(String* string);

void freeListString(String** list, int size);

void freeString(String* string);


#endif