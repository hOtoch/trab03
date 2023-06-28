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
    strcpy(pathStopWords, strcat(dir,"/stopwords.txt"));
    String* pathStopWordsString = createString(pathStopWords);
    String** stopWordsList;
    
    stopWordsList = leArquivo(pathStopWordsString, maxSwCount, auxSwCount);

    qsort(stopWordsList, swCount, sizeof(String*), compareQs);

    // for(int i = 0; i < swCount; i++){
    //     printf("%s\n", getString(stopWordsList[i]));
    // }

    
    // ----- Leitura do arquivo Index -----

    char* pathIndex = strcat(strdup(dir),"/index.txt");
    
    String* pathIndexString = createString(pathIndex);

    int maxPagesCount = 50, countPages = 0;
    int *auxCountPages = &countPages;
    String** indexList;

    indexList = leArquivo(pathIndexString, maxPagesCount, auxCountPages);


    
    // ----- Leitura do graph.txt e criação das paginas -----
   
    char* dirAux = strdup(dir); // dir sendo alterado dentro da função createPages, verificar depois
    // printf("%s\n",dirAux);
    char* pathGraph = strcat(strdup(dir),"/graph.txt");
    

    Page** pages = createPages(pathGraph,countPages);
    
    // for(int i = 0; i < countPages; i++){
    //     printf("%s : ", getNome(pages[i]));
    //     for(int j = 0; j < getCountLinks(pages[i]); j++){
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

        // printf("%s\n", result);
        FILE* filePage = fopen(result, "r");

        if(verificaArquivo(filePage)){
            while(!feof(filePage)){
                getline(&line, &len, filePage);
                termo = strtok(line, " ");
                while(termo != NULL){
                    // printf("%s\n", termo);

                    // Verificar se eh stopword (busca binaria)
                    root = RBT_insert(root, createString(termo), pages[i]);
                    
                    termo = strtok(NULL, " ");
                }          

            }
        }else{
            perror("Error: ");
            exit(1); 
        }

        printRBT(root);

        break;
    }

    

    return 0;    
}