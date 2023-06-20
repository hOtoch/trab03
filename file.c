#include "file.h"



char** leArquivo(char* path, int maxCount, int *count){
    char** list = (char**)malloc(maxCount *sizeof(char*));
    char* line = malloc(sizeof(char)*1000);
    size_t len = 0;
    FILE* arq = fopen(path, "r");

    if(verificaArquivo(arq)){
        while(!feof(arq)){
            
            list[*count] = malloc(sizeof(char)*100);
            getline(&line, &len, arq);
            strcpy(list[*count], line);
            // printf("%s\n", list[i]);
            *count = *count + 1;

            if(*count == maxCount){               
                maxCount *= 2;
                list = realloc(list, sizeof(char*)*maxCount);
                printf("Deu realloc\n");
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
    }

    return 1;
}