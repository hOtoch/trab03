#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "file.h"


int main(int argc, char* argv[]){

    // Nome do diretorio que contem as pastas dado nos argumentos
    char* dir = argv[1];
    

    /*  
        ----- Vetor de Strings StopWords ----- 
        
        De inicio são alocadas 100 (maxCount) posicoes do vetor, 
        caso existam mais do que maxCount palavras é realizado o Realloc e a continuação da leitura.
        
        A cada realloc maxSwCount é multiplicado por 2.
    */
    int swCount = 0,maxSwCount = 1000;
    int *auxSwCount = &swCount;
    char* pathStopWords = strcat(strdup(dir),"/stopwords.txt");
    char** stopWordsList;
    
    stopWordsList = leArquivo(pathStopWords, maxSwCount, auxSwCount);

    // for(int i = 0; i < swCount; i++){
    //     printf("%s\n", stopWordsList[i]);
    // }
    

    // ----- Indexador ------

    char* pathIndex = strcat(strdup(dir),"/index.txt");
    int maxPagesCount = 50, countPages = 0;
    int *auxCountPages = &countPages;
    char** indexList;

    indexList = leArquivo(pathIndex, maxPagesCount, auxCountPages);
   
    // for(int i = 0; i < countPages; i++){
    //     printf("%s\n", indexList[i]);
    // }
    


    // ----- Leitura das buscas -----
    char* pathSearches = strcat(strdup(dir),"/searches.txt");
    FILE* searches = fopen(pathSearches, "r");

    if (searches == NULL){
        perror("Error: ");
        exit(1);
    }

    char* pathAllPages = strcat(strdup(dir),"/pages/");
    char* search = malloc(sizeof(char)*100);
    char* line = malloc(sizeof(char)*1000);
    size_t len = 0;
    
    while(!feof(searches)){
        getline(&search, &len, searches);
        
        for(int i = 0; i < countPages; i++){
            char* pathPage = strcat(strdup(pathAllPages), indexList[i]);
            // printf("%s\n", pathPage);
            //FILE* page = fopen(pathPage, "r");

            // if (page == NULL){
            //     perror("Error: ");
            //     exit(1);
            // }

            // while(!feof(page)){
            //     getline(&line, &len, page);
                
            //     char* word = strtok(line, " ");
            //     while(word != NULL){
                    
            //         if(verifyStopWord(word, stopWordsList, swCount)){
            //             printf("%s ", indexList[i]);
            //         }

            //         word = strtok(NULL, " ");
            //     }
            // }

            // fclose(page);

        }

    }
    
    free(search);
    fclose(searches);

    return 0;    
}