#include "file.h"
#include <string.h>
#include "utils.h"
#include "TST.h"

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

TST* leArquivoTST(String* path, int maxCount, int *count){
    TST* rootGraph = NULL;
    char* line = (char*) malloc(sizeof(char)*100);
    size_t len = 0;
    int i = 0;
    FILE* arq = fopen(getString(path), "r");

    if(verificaArquivo(arq)){
        while(!feof(arq)){
            getline(&line, &len, arq);
            String* auxLine = createString(line);
            removeNewLine(auxLine);


            TST* result = (TST*)TST_search(rootGraph, auxLine);
            if(result == NULL){
                TST* value = NULL;
                value = TST_insert(value, auxLine,newPage(getString(auxLine),0)); // Criando a TST value da pagina a ser inserida
                rootGraph = TST_insert(rootGraph, auxLine, (TST*)value);
                *count = *count + 1;
            }else{
                result = TST_insert(result, auxLine, newPage(getString(auxLine),0));
                *count = *count + 1;
            }
        }
    }else{
        exit(1);
    }

    fclose(arq);
    return rootGraph;
    
}


int verificaArquivo(FILE* arquivo){
    if(arquivo == NULL){
        perror("Error: ");
        return 0;
    }else{
        return 1;
    }

}