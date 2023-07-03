#include "page.h"
#include "string.h"
#include "utils.h"

struct page {
    String* nome;
    int countInLinks;
    int countOutLinks;
    double pageRank;
    Page** outLinks
    Page** inLinks;
};

Page* getPageByName(Page** pages, int countPages, const String* nome) {
    for (int i = 0; i < countPages; i++) {
        if(compare(nome, pages[i]->nome) == 0){
            return pages[i];
        }
    }
    return NULL;
}


Page** createPages(char* path, int countPages) {
    char* line = NULL;
    size_t len = 0;
    removeNewLine(createString(path));
    FILE* graph = fopen(path, "r");

    char* nome = (char*) malloc(sizeof(char) * 100);  

    int countLinks;

    Page** pages = (Page**) malloc(sizeof(Page*) * countPages);

    for (int i = 0; i < countPages; i++) {

        getline(&line, &len, graph);

        token = strtok(line, " ");
        strcpy(nome, token);

        token = strtok(NULL, " ");
        countOutLinks = atoi(token);
        token = strtok(NULL, " ");

        if(pages[i] == NULL){ // caso nao tenhamos uma pagina criada nessa posiçao
            Page* page = newPage(nome, countOutLinks);
            pages[i] = page;
        }else{
            Page* page = pages[i];
        }

        page->outLinks = (Page**) malloc(sizeof(Page*) * countOutLinks);

        for (int j = 0; j < countOutLinks; j++) {
            token = strtok(NULL, " ");
            String* linkNome = createString(token);

            Page* linkPage = getPageByName(pages, i, linkNome);

            if (linkPage == NULL) {
                linkPage = newPage(linkNome, 0);
                pages[i+1+j] = linkPage;
            }

            // Adicionando a página atual como InLink na página linkPage
            linkPage->countInLinks++;
            linkPage->inLinks = (Page**) realloc(linkPage->inLinks, sizeof(Page*) * linkPage->countInLinks);
            linkPage->inLinks[linkPage->countInLinks - 1] = page;

            // Adicionando a página linkPage como OutLink na página atual
            page->outLinks[j] = linkPage;
          
        }
        
    }
    fclose(graph);
    free(nome); 
    free(line);
    return pages;
}


String* getNome(Page* page){
    return page->nome;
}

int getCountLinks(Page* page){
    return page->countLinks;
}

String** getLinks(Page* page){
    return page->links;
}

Page* getPage(Page** page, int i){
    return page[i];
}

double getPageRank(Page* page){
    return page->pageRank;
}

void setPageRank(Page* page, double pageRank){
    page->pageRank = pageRank;
}

Page* newPage(char* nome, int countLinks){
    Page* page = (Page*)malloc(sizeof(Page));
    page->nome = createString(nome);
    page->pageRank = 0;
    page->countInLinks = 0;
    page->countOutLinks = countLinks;
    page->inLinks = NULL;
    page->outLinks = NULL;
    return page;
}

void freePages(Page** pages, int countPages){
    for(int i = 0; i < countPages; i++){
        freePage(pages[i]);
    }
    free(pages);
}

void freePage(Page* page){
    free(page->nome);
    free(page->links);
    free(page);
}

