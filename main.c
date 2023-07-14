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

    stopWordsList = leArquivo(pathStopWordsString, maxSwCount, auxSwCount);

    qsort(stopWordsList, swCount, sizeof(String *), compareQs);


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

    char *pathGraph = malloc(sizeof(char) * (strlen(dir) + strlen("/graph.txt") + 1));
    strcpy(pathGraph, dir);
    strcat(pathGraph, "/graph.txt");
    size_t len = 10000;
    char *line = (char *)malloc(sizeof(char) * len);
    char *termo;
    String* nameP1;
    int countOutLinks;

    FILE* fileGraph = fopen(pathGraph, "r");
    
    for(int i = 0; i < countPages; i++){
        getline(&line, &len, fileGraph);
        termo = strtok(line, " ");
        nameP1 = createString(termo);
        removeNewLine(nameP1);
    
        countOutLinks = atoi(strtok(NULL, " "));
        
        TST* resultTST = (TST*)TST_search(pagesTST, nameP1);
        Page* p1 = (Page*)TST_search(resultTST, nameP1);
        
      
        setCountOutLinks(p1, countOutLinks); // Atualizando o countOutLinks da pagina
        
        setPageRank(p1, (double)(1.0/countPages));
        setOldPageRank(p1, (double)(1.0/countPages));
        for(int i = 0; i < countOutLinks; i++){
            termo = strtok(NULL, " ");
            String* nameP2 = createString(termo);
            removeNewLine(nameP2);

            TST* resultTST = (TST*)TST_search(pagesTST, nameP2);
            Page* p2 = (Page*)TST_search(resultTST, nameP2);
    
            setCountInLinks(p2, getCountInLinks(p2) + 1);

            /* Inserindo a pagina p1[0] na arvore de páginas que contem um link para a pagina p2[0]*/
            TST* root = getLinks(p2);
            root = TST_insert(root, nameP1, (Page*) p1);
            setLinks(p2, root);
            
            freeString(nameP2);
        }
        freeString(nameP1);
    }
    fclose(fileGraph);

    // Page* page_test = (Page*)TST_search(pagesTST,createString("51.txt"));
    // if(page_test != NULL){
    //     printf("Nome PAGE RESULT: %s\n", getString(getNome(page_test)));
    // }else{
    //     printf("Nao encontrado\n");
    // }
    


    /* ------------- Indexador -------------- */ 
    char *dirAux = malloc(sizeof(char) * (strlen(dir) + strlen("/pages/") + 1));
    strcpy(dirAux, dir);
    strcat(dirAux, "/pages/");
   
    TST *indexadorTST = NULL;

    indexadorTST = searchAndIndex(indexadorTST, pagesTST, dirAux, stopWordsList, swCount);



    /* -------- Calculando os Page Ranks ----------- */

    double stopValue = 1;
    int countIterations = 0;
    while(stopValue >= 1e-6){
        calculatePageRank(pagesTST,countPages);
        stopValue = (double)((1.0/countPages) * calculateEndPageRank(pagesTST, 0.0));
    }
    
    // TST* result_test = (TST*)TST_search(indexadorTST, createString("recognised"));
    // if(result_test != NULL){
    //     searchAndPrint(result_test);
    // }else{
    //     printf("Nao encontrado\n");
    // }


    /* ---------- Processador de Consultas ---------- */

    TST* firstTST = NULL;
    TST* secondTST = NULL;

    while(scanf("%[^\n]s", line) == 1){
        scanf("\n");
        int indice = 0;
        String *linha = createString(line);
        removeNewLine(linha);
        printf("search:%s\n", getString(linha));

        termo = strtok(line, " ");
        String *termoBusca = createString(termo);
        removeNewLine(termoBusca);

        firstTST = (TST *)TST_search(indexadorTST, termoBusca);
        freeString(termoBusca);
        Page **paginasComum = malloc(countPages * sizeof(Page *));
        termo = strtok(NULL, " ");
        if (termo == NULL)
        {
            paginasComum = TST_intersecao(firstTST, firstTST, paginasComum, &indice);
        }
        else
        {
            while (termo != NULL)
            {
                String *termoBusca = createString(termo);
                removeNewLine(termoBusca);
                secondTST = (TST *)TST_search(indexadorTST, termoBusca);
                paginasComum = TST_intersecao(firstTST, secondTST, paginasComum, &indice);
                termo = strtok(NULL, " ");
                freeString(termoBusca);
            }
        }

        qsort(paginasComum, indice, sizeof(Page *), comparePR);
        printf("pages:");

        if(indice == 1){
            printf("%s\n", getString(getNome(paginasComum[0])));
            printf("pr:");
            printf("%lf", getPageRank(paginasComum[0]));
        }else{
            for (int i = 0; i < indice; i++){
                if(i == (indice-1)){
                    printf("%s", getString(getNome(paginasComum[i])));
                }else{
                    printf("%s ", getString(getNome(paginasComum[i])));
                }
                
            }
            printf("\npr:");
            for (int i = 0; i < indice; i++){
                if(i == (indice-1)){
                    printf("%lf", getPageRank(paginasComum[i]));
                }else{
                    printf("%lf ", getPageRank(paginasComum[i]));
                }
                
            }
        }
        printf("\n");
        free(paginasComum);
        freeString(linha);
    }

    // ---- Liberação de memória -----
    freeListString(stopWordsList, swCount);
    freeString(pathStopWordsString);
    free(pathStopWords);
    free(pathIndex);
    freeString(pathIndexString);
    free(dirAux);
    free(pathGraph);
    free(line);
    //Liberando memoria pra lista de stopwords
    // freeListString(stopWordsList, swCount);

    //Liberando memoria pra TST de pages
    
    TST_destroi(pagesTST, freePagesTST);
    TST_destroi(indexadorTST, freeTST);
    
    //Liberando memoria pra TST de indexador
    // TST_Destroi(indexadorTST);

    return 0;
}
