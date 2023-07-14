#include "utils.h"
#include "math.h"
#include "page.h"
#include "TST.h"


int verifyStopWord(char *word, char **stopWordsList, int countStopWords)
{
    int i;
    for (i = 0; i < countStopWords; i++)
    {
        if (strcmp(word, stopWordsList[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void searchAndPrint(TST* indexTST){
    if(indexTST){
        Page* result = (Page*)getValues(indexTST);
        if(result != NULL){
            printf("Página %s - PR: %f\n", getString(getNome(result)), getOldPageRank(result));
        }

        searchAndPrint(getLeft(indexTST));
        searchAndPrint(getMid(indexTST));
        searchAndPrint(getRight(indexTST));
    }
}

int comparePR(const void* a, const void* b) {
    Page** valueA = (Page**)a;
    Page** valueB = (Page**)b;

    double pageRankA = getPageRank(*valueA);
    double pageRankB = getPageRank(*valueB);

    if (pageRankA > pageRankB) {
        return -1;
    } else if (pageRankA < pageRankB) {
        return 1;
    } else {
        return compare(getNome(*valueA), getNome(*valueB));
    }
}

double calculateSumInLinks(TST* inLinks, double sum, char* iteracao){
    if(inLinks){
        String *iteracaoString = createString(iteracao);
        if(getValues(inLinks) != NULL){
            Page* page = (Page*)getFirstElement(inLinks);
            if(compare(iteracaoString, getNome(page)) == 1){
                sum += getOldPageRank(page)/fabs(getCountOutLinks(page));
            }else{
                sum += getPageRank(page)/fabs(getCountOutLinks(page));
            }
        }
        freeString(iteracaoString);
        sum = calculateSumInLinks(getLeft(inLinks), sum, iteracao);
        sum = calculateSumInLinks(getMid(inLinks), sum, iteracao);
        sum = calculateSumInLinks(getRight(inLinks), sum, iteracao);
    }
    
    return sum;
}

void calculatePageRank(TST* pages, int countPages){
    if(pages){
        if(getValues(pages) != NULL){
        
            TST* tstResult = (TST*)getValues(pages);
            Page* pagina = (Page*)getFirstElement(tstResult);

            double baseValue = (1-0.85)/countPages;
            TST* links = getLinks(pagina);
            double sumInLinks = calculateSumInLinks(links, 0.0, getString(getNome(pagina)));
           
            double pageRank = 0.0;

            if(getCountOutLinks(pagina) != 0){
                pageRank = baseValue + 0.85*sumInLinks;
            }else{
                pageRank = baseValue + (0.85*getPageRank(pagina)) + 0.85*sumInLinks;
            }
            
            setOldPageRank(pagina, getPageRank(pagina));
            setPageRank(pagina, pageRank);
            
        }
        
        calculatePageRank(getLeft(pages), countPages);
        calculatePageRank(getMid(pages), countPages);
        calculatePageRank(getRight(pages), countPages);
    }
        
}



TST* searchAndIndex(TST * indexTST, TST *pages, char *pathPage, String **stopWordsList, int swCount)
{

    if (pages)
    {
        if (getValues(pages) != NULL)
        {
            TST* result = (TST*)getValues(pages);
            Page* pageResult = (Page*)getFirstElement(result);
            // printf("Page a ser indexada: %s\n", getString(getNome(pageResult)));
            indexTST = indexador(indexTST, pageResult, pathPage, stopWordsList, swCount);

        }
        indexTST = searchAndIndex(indexTST, getLeft(pages), pathPage, stopWordsList, swCount);
        indexTST = searchAndIndex(indexTST, getMid(pages), pathPage, stopWordsList, swCount);
        indexTST = searchAndIndex(indexTST, getRight(pages), pathPage, stopWordsList, swCount);

    }
    return indexTST;
}

double calculateEndPageRank(TST* pages, double value){
    if(pages){
        if(getValues(pages) != NULL){
            TST* tstResult = (TST*)getValues(pages);
            Page* pagina = (Page*)getFirstElement(tstResult);
            value += fabs(getPageRank(pagina) - getOldPageRank(pagina));
        }

        value = calculateEndPageRank(getLeft(pages), value);
        value = calculateEndPageRank(getMid(pages), value);
        value = calculateEndPageRank(getRight(pages), value);
    }

    return value;
}

TST* indexador(TST *indexTST, Page *page, char *pathPage, String **stopWordsList, int swCount)
{
    char result[1000];
    size_t len = 10000;
    char *line = (char *)malloc(sizeof(char) * len);
    char *termo;


    strcpy(result, pathPage);
    strcat(result, getString(getNome(page))); /* Definindo o caminho dos arquivos */
    String* resultString = createString(result);
    removeNewLine(resultString);
    String *termoString;


    FILE *filePage = fopen(getString(resultString), "r");

    if (verificaArquivo(filePage))
    {
        while (!feof(filePage))
        {
            getline(&line, &len, filePage);
            termo = strtok(line, " ");

            while (termo != NULL)
            {
                /* Remove o \n e transforma todas as letras em lowcase */
                termoString = createString(termo);
                toLowerCase(termoString);
                removeNewLine(termoString);

                // Verificar se eh stopword (busca binaria)
                int index = binarySearch(stopWordsList, 0, swCount - 1, getString(termoString));

                if (index == -1){
                    TST* result = (TST*) TST_search(indexTST, termoString);
                    if(result == NULL){
                        TST* newTST = NULL;
                        newTST = TST_insert(newTST, getNome(page),(Page*) page);
                        indexTST = TST_insert(indexTST, termoString,(TST*)newTST);

                    }else{
                        result = TST_insert(result, getNome(page),(Page*) page);
                        //indexTST = TST_insert(indexTST, termoString, (TST*)resultTST);
                    }
                } 

                termo = strtok(NULL, " ");
                freeString(termoString);
            }
        }
         
        fclose(filePage);
    }
    else
    {
        perror("Error: ");
        exit(1);
    }
    freeString(resultString);
    free(line);
    return indexTST;
}


int binarySearch(String **arr, int left, int right, char *key)
{

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        // printf("left = %d, right = %d, mid = %d\n", left, right,mid);
        // printf("comparando %s com %s\n", key, getString(arr[mid]));
        String* keyString = createString(key);
        int cmp = compare(keyString, arr[mid]);
        freeString(keyString);
        if (cmp == 0)
        {
            return mid;
        }

        else if (cmp < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}


void freeArray(void **ptr) {
    if (ptr) {
        for (size_t i = 0; ptr[i]; i++) {
            free(ptr[i]);
        }
        free(ptr);
    }
}
