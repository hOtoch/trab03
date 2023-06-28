#include "string.h"
#include <string.h>


struct string{
    char* str;
    int size;
};

String* createString(char* str){
    String* string = (String*) malloc(sizeof(String));
    string->str = strdup(str);
    string->size = strlen(str);
    return string;
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


void freeString(String* string){
    free(string->str);
    free(string);
}