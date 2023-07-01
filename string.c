#include "string.h"
#include <string.h>
#include <ctype.h>

struct string{
    char* str;
    int size;
};

String* createString(char* str){
    String* string = (String*) malloc(sizeof(String));
    string->size = strlen(str);
    string->str = (char*) malloc(sizeof(char)*(string->size+1));
    strcpy(string->str, str);
    return string;
}

void toLowerCase(String* str) {
    int i = 0;
    char* string = getString(str);
    while (string[i]) {
        string[i] = tolower(string[i]);
        i++;
    }
}

void removeNewLine(String* str) {
    char* string = getString(str);
    if (getSize(str) > 0 && string[getSize(str) - 1] == '\n') {  
        string[getSize(str) - 1] = '\0';
        setSize(str, getSize(str) - 1);
    }
}

int setSize(String* str, int size){
    str->size = size;
    return 0;
}


int compare_from(String *s, String *t, int d) {
    int min = s->size < t->size ? s->size : t->size;

    for (int i = d; i < min; i++) {
        if (s->str[i] < t->str[i]) { return -1; }
        if (s->str[i] > t->str[i]) { return 1; }
    }
    return s->size - t->size;
}

int compare(String *s, String *t) {
    return compare_from(s, t, 0);
}

int compareQs(const void* a, const void* b) {
    const String* strA = *(const String**)a;
    const String* strB = *(const String**)b;

    String tempA = *strA;  // Cópia mutável de strA
    String tempB = *strB;  // Cópia mutável de strB

    return compare_from(&tempA, &tempB, 0);
}

char* getString(String* string){
    return string->str;
}

int getSize(String* string){
    return string->size;
}

void freeListString(String** list, int size){
    for(int i = 0; i < size; i++){
        freeString(list[i]);
    }
    free(list);
}


void freeString(String* string){
    free(string->str);
    free(string);
}
