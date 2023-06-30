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



int binarySearch(String** arr, int left, int right, char* key) {

    while (left <= right) {
        int mid = left + (right - left) / 2;
        // printf("left = %d, right = %d, mid = %d\n", left, right,mid);
        // printf("comparando %s com %s\n", key, getString(arr[mid]));
        int cmp = compare(createString(key), arr[mid]);
        
        
        if (cmp == 0){
            return mid;
        }
        
        else if (cmp < 0)
            right = mid - 1;
        else
            left = mid + 1;

        
    }
    
    return -1;
}

