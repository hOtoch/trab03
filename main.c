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
    char *dir = argv[1];

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

        for(int i = 0; i < countOutLinks; i++){
            termo = strtok(NULL, " ");
            String* nameP2 = createString(termo);
            removeNewLine(nameP2);

            Page** p2 = TST_search(pagesTST, nameP2);
            setCountInLinks(p2[0], getCountInLinks(p2[0]) + 1);
            // printf("NOME P2: %s, COUNT IN LINKS: %d\n", getString(getNome(p2[0])), getCountInLinks(p2[0]));
            
            
            TST_insert(getLinks(p2[0]), nameP1, (Page*) p1[0]); // PROBLEMA AQUI!!!!!!!!!!!!!!!!!!!!!!!!
            Page** resultP = TST_search(getLinks(p2[0]), nameP1);
        }

    }

    Page** searchPage = TST_search(pagesTST, createString("24011.txt"));
    printf("NOME SEARCH PAGE: %s\n", getString(getNome(searchPage[0])));
    printf("Links: %d\n", getCountInLinks(searchPage[0]));
    
    Page** resultPage = TST_search(getLinks(searchPage[0]), createString("3391.txt"));
    
    // printf("NOME RESULT PAGE: %s\n", getString(getNome(resultPage[0])));


    // for (int i = 0; i < countPages; i++) {
    //     printf("%s : ", getString(getNome(pages[i])));
    //     printf("\n");
    // }

    // ----- Indexador ------

    char *pathPage = strcat(dirAux, "/pages/");
    char result[100];
    TST *root = NULL;

    // for (int i = 0; i < countPages; i++)
    // {
    //     strcpy(result, pathPage);
    //     strcat(result, getString(indexList[i])); /* Definindo o caminho dos arquivos */

    //     removeNewLine(createString(result));

    //     // printf("entrou no for %s\n", result);
    //     FILE *filePage = fopen(result, "r");

    //     if (verificaArquivo(filePage))
    //     {

    //         while (!feof(filePage))
    //         {
    //             getline(&line, &len, filePage);

    //             // printf("\n\nLINHA: %s\n\n", line);
    //             termo = strtok(line, " ");

    //             while (termo != NULL)
    //             {
    //                 /* Remove o \n e transforma todas as letras em lowcase */
    //                 String *termoString = createString(termo);

    //                 toLowerCase(termoString);
    //                 removeNewLine(termoString);

    //                 // printf("Termo: %s", getString(termoString));

    //                 // Verificar se eh stopword (busca binaria)
    //                 int index = binarySearch(stopWordsList, 0, swCount - 1, getString(termoString));

    //                 if (index == -1)
    //                 {
    //                     // printf("--- Termo <%s> nao eh stopword ---\n", getString(termoString));
    //                     // root = RBT_insert(root, termoString, pages[i]); 
    //                     root = TST_insert(root, termoString, pages[i]);
    //                 }
    //                 else
    //                 {
    //                     // printf("--- Termo <%s> eh stopword ---\n", getString(termoString));
    //                 }

    //                 termo = strtok(NULL, " ");
    //                 // printf("--------------------------------------------------------------------\n");
    //             }
    //         }
    //         fclose(filePage); 
    //     }
    //     else
    //         {
    //         perror("Error: ");
    //         exit(1);
    //     }
    // }
    // Page** resultPages = TST_search(root, createString("man"));
    
    // printRBT(root);
    

    // Liberação de memória -----
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
