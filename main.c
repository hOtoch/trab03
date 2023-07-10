#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "page.h"
#include "file.h"
#include "TST.h"

int main(int argc, char *argv[])
{
    // Nome do diretorio que contem as pastas dado nos argumentos
    char *dir = "exemplo3";

    // ----- Vetor de Strings StopWords -----

    int swCount = 0, maxSwCount = 1000;
    int *auxSwCount = &swCount;
    char *pathStopWords = malloc(sizeof(char) * (strlen(dir) + strlen("/stopwords.txt") + 1));
    strcpy(pathStopWords, dir);
    strcat(pathStopWords, "/stopwords.txt");
    String *pathStopWordsString = createString(pathStopWords);
    String **stopWordsList;

    // printf("%s\n", getString(pathStopWordsString));

    stopWordsList = leArquivo(pathStopWordsString, maxSwCount, auxSwCount);
    // printf("%d\n", swCount);

    qsort(stopWordsList, swCount, sizeof(String *), compareQs);

    // for(int i = 0; i < swCount; i++){
    //     printf("%d - %s\n", i,getString(stopWordsList[i]));
    // }

    // ----- Leitura do arquivo Index e inicialização da TST de pages  -----

    char *pathIndex = malloc(sizeof(char) * (strlen(dir) + strlen("/index.txt") + 1));
    strcpy(pathIndex, dir);
    strcat(pathIndex, "/index.txt");
    String *pathIndexString = createString(pathIndex);
    int maxPagesCount = 50, countPages = 0;
    int *auxCountPages = &countPages;
    TST* pagesTST = NULL;

    
    pagesTST = leArquivoTST(pathIndexString, maxPagesCount, auxCountPages);

    
    // ----- Leitura do graph.txt e inserção dos valores da TST de pages -----

    char *dirAux = malloc(sizeof(char) * (strlen(dir) + strlen("/pages") + 1));
    strcpy(dirAux, dir);
    char *pathGraph = malloc(sizeof(char) * (strlen(dir) + strlen("/graph.txt") + 1));
    strcpy(pathGraph, dir);
    strcat(pathGraph, "/graph.txt");
    char *line = (char *)malloc(sizeof(char) * 100);
    size_t len = 0;
    char *termo;
    String* nameP1;
    int countOutLinks;
    String** conexoes;
    FILE* fileGraph = fopen(pathGraph, "r");
    
    for(int i = 0; i < countPages; i++){
        getline(&line, &len, fileGraph);
        nameP1 = createString(strtok(line, " "));
        countOutLinks = atoi(strtok(NULL, " "));
        
        Page** p1 = TST_search(pagesTST, nameP1);
        
        setCountOutLinks(p1[0], countOutLinks); // Atualizando o countOutLinks da pagina
        setPageRank(p1[0], (double)(1.0/countPages));
        setOldPageRank(p1[0], (double)(1.0/countPages));
        for(int i = 0; i < countOutLinks; i++){
            termo = strtok(NULL, " ");
            String* nameP2 = createString(termo);
            removeNewLine(nameP2);

            Page** p2 = TST_search(pagesTST, nameP2);
            setCountInLinks(p2[0], getCountInLinks(p2[0]) + 1);

            
            TST* root = getLinks(p2[0]);
            
            /* Inserindo a pagina p1[0] na arvore de páginas que contem um link para a pagina p2[0]*/
            root = TST_insert(root, nameP1, (Page*) p1[0]); 

            setLinks(p2[0], root);
            
        }
       

    }

    

    // Page** searchPage = TST_search(pagesTST, createString("12241.txt"));
    // printf("NOME SEARCH PAGE: %s\n", getString(getNome(searchPage[0])));
    // printf("Links: %d\n", getCountInLinks(searchPage[0]));
    
    // Page** resultPage = TST_search(getLinks(searchPage[0]), createString("20474.txt"));
    
    // printf("NOME RESULT PAGE: %s\n", getString(getNome(resultPage[0])));




    /* ------------- Indexador -------------- */ 

    char *pathPage = strcat(dirAux, "/pages/");
   
    TST *indexadorTST = NULL;

    indexadorTST = searchAndIndex(indexadorTST, pagesTST, pathPage, stopWordsList, swCount);


    // -------- Page Rank ----------

    /* -------- Calculando os Page Ranks ----------- */

    double stopValue = 1;
    int countIterations = 0;
    while(stopValue >= 1e-6){
        // calcula page rank
        printf("ITERAÇÃO: %d\n", countIterations++);
        calculatePageRank(pagesTST,countPages);
        stopValue = (double)((1.0/countPages) * calculateEndPageRank(pagesTST, 0.0));
        printf("Stop Value: %lf\n", stopValue);
        printf("-----------------------------------------------------------------------------\n");
    }



    // ---- Liberação de memória -----
    // freeListString(stopWordsList, swCount);
    // freeListString(indexList, countPages);
    // freePages(pages, countPages);
    // free(dir);
    free(pathStopWords);
    freeString(pathStopWordsString);
    free(pathIndex);
    freeString(pathIndexString);
    free(dirAux);
    free(line);

    return 0;
}
