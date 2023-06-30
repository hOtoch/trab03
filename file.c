#include "file.h"
#include <string.h>
#include "utils.h"

String** leArquivo(String* path, int maxCount, int *count){
    String** list = (String**)malloc(maxCount *sizeof(String*));
    char* line = (char*) malloc(sizeof(char)*100);
    size_t len = 0;
    FILE* arq = fopen(getString(path), "r");

    if(verificaArquivo(arq)){
        while(!feof(arq)){
            getline(&line, &len, arq);
            String* auxLine = createString(line);
            removeNewLine(auxLine);
            list[*count] = auxLine;
        
            // printf("%s\n", list[i]);
            *count = *count + 1;

            if(*count == maxCount){               
                maxCount *= 2;
                list = realloc(list, sizeof(String*)*maxCount);
            }
           
        }
    }else{
        exit(1);
    }

    fclose(arq);
    return list;
    
}


int verificaArquivo(FILE* arquivo){
    if(arquivo == NULL){
        perror("Error: ");
        return 0;
    }else{
        return 1;
    }

}