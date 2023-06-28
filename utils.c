#include "utils.h"


int verifyStopWord(char* word, char** stopWordsList, int countStopWords){
    int i;
    for(i = 0; i < countStopWords; i++){
        if(strcmp(word, stopWordsList[i]) == 0){
            return 1;
        }
    }
    return 0;
}


void removeNewLine(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

