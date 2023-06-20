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