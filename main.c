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
    char* pathStopWords = malloc(sizeof(char) * (strlen(dir) + strlen("/stopwords.txt") + 1));
    strcpy(pathStopWords, dir);
    strcat(pathStopWords, "/stopwords.txt");
    String* pathStopWordsString = createString(pathStopWords);
    String** stopWordsList;


   //printf("%s\n", getString(pathStopWordsString));
    
    stopWordsList = leArquivo(pathStopWordsString, maxSwCount, auxSwCount);
    //printf("%d\n", swCount);

    qsort(stopWordsList, swCount, sizeof(String*), compareQs);

    // for(int i = 0; i < swCount; i++){
    //     printf("%s\n", getString(stopWordsList[i]));
    // }

    
    // ----- Leitura do arquivo Index -----

    char* pathIndex = malloc(sizeof(char) * (strlen(dir) + strlen("/index.txt") + 1));
    strcpy(pathIndex, dir);
    strcat(pathIndex, "/index.txt");
    String* pathIndexString = createString(pathIndex);
    int maxPagesCount = 50, countPages = 0;
    int *auxCountPages = &countPages;
    String** indexList;

    indexList = leArquivo(pathIndexString, maxPagesCount, auxCountPages);
    //printf("%d\n", countPages);


    
    // ----- Leitura do graph.txt e criação das paginas -----
   
    char* dirAux = malloc(sizeof(char) * (strlen(dir) + strlen("/pages") + 1));
    strcpy(dirAux, dir);
    char* pathGraph = malloc(sizeof(char) * (strlen(dir) + strlen("/graph.txt") + 1));
    strcpy(pathGraph, dir);
    strcat(pathGraph, "/graph.txt");

    Page** pages = createPages(pathGraph, countPages);

    // for (int i = 0; i < countPages; i++) {
    //     printf("%s : ", getNome(pages[i]));
    //     for (int j = 0; j < getCountLinks(pages[i]); j++) {
    //         printf("%s ", getString(getLinks(pages[i])[j]));
    //     }
    //     printf("\n");
    // }


    // ----- Indexador ------
    
    char* pathPage = strcat(dirAux,"/pages/");
    char result[100];
    char* line = (char*) malloc(sizeof(char)*100);
    size_t len = 0;
    char* termo;
    RBT* root = NULL;

    for(int i = 0; i < countPages; i++){
        strcpy(result, pathPage);
        strcat(result, getString(indexList[i])); /* Definindo o caminho dos arquivos */
        
        removeNewLine(result);

        //printf("entrou no for %s\n", result);
        FILE* filePage = fopen(result, "r");

        if(verificaArquivo(filePage)){
            while(!feof(filePage)){
                getline(&line, &len, filePage);
                termo = strtok(line, " ");
                while(termo != NULL){

                    // Verificar se eh stopword (busca binaria)
                    int index = binarySearch(stopWordsList, 0, swCount, termo);
                    printf("index: %d\n", index);
                    if(index != -1){
                        printf("entrou no if\n");
                        termo = strtok(NULL, " ");
                        continue;
                        printf("entrou no if\n");
                    }
                    printf("saiu do if\n");
                    root = RBT_insert(root, createString(termo), pages[i]);// Nao ta inserindo certo
                    printf("inseriu\n");
                    
                    termo = strtok(NULL, " ");

                }          

            }
        }else{
            perror("Error: ");
            exit(1); 
        }

        //printRBT(root);

        break;
    }

    //Liberação de memória -----
    for (int i = 0; i < swCount; i++) {
        freeString(stopWordsList[i]);
    }
    free(stopWordsList);

    // for (int i = 0; i < countPages; i++) {
    //     freePage(pages[i]);
    // }
    // free(pages);

    // for (int i = 0; i < countPages; i++) {
    //     freeString(indexList[i]);
    // }
    // free(indexList);

    free(dir);
    free(pathStopWords);
    freeString(pathStopWordsString);
    free(pathIndex);
    freeString(pathIndexString);
    free(dirAux);
    free(line);

    

    return 0;    
}
