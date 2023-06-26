#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "file.h"


int main(int argc, char* argv[]){
    // Nome do diretorio que contem as pastas dado nos argumentos
    char* dir = argv[1];

    // ----- Vetor de Strings StopWords ----- 
    
    int swCount = 0,maxSwCount = 1000;
    int *auxSwCount = &swCount;
    char* pathStopWords = strcat(strdup(dir),"/stopwords.txt");
    String* pathStopWordsString = createString(pathStopWords);
    String** stopWordsList;
    
    stopWordsList = leArquivo(pathStopWordsString, maxSwCount, auxSwCount);
    

    // ----- Indexador ------

    char* pathIndex = strcat(strdup(dir),"/index.txt");
    String* pathIndexString = createString(pathIndex);

    int maxPagesCount = 50, countPages = 0;
    int *auxCountPages = &countPages;
    String** indexList;

    indexList = leArquivo(pathIndexString, maxPagesCount, auxCountPages);
    char* pathPage = strcat(strdup(dir),"/pages/");
    char result[100];
    char* line = (char*) malloc(sizeof(char)*100);
    size_t len = 0;
    char currentDirectory[1024];
    for(int i = 0; i < countPages; i++){
        strcpy(result, pathPage);
        strcat(result, getString(indexList[i])); /* Definindo o caminho dos arquivos */
        printf("%s\n", result);


        
        FILE* page = fopen(result, "r");


        // if(verificaArquivo(page)){
        //     while(!feof(page)){
        //         getline(&line, &len, page);
        //         printf("%s\n", line);
        //     }
        // }else{
        //     perror("Error: ");
        //     exit(1);
        // }

    }




    return 0;    
}