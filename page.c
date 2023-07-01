#include "page.h"
#include "string.h"
#include "utils.h"

struct page {
    String* nome;
    int countLinks;
    String** links;
};

Page** createPages(char* path, int countPages) {
    char* line = (char*) malloc(sizeof(char) * 100);
    size_t len = 0;
    removeNewLine(createString(path));
    FILE* graph = fopen(path, "r");

    char* token;
    char* nome = (char*) malloc(sizeof(char) * 100);  

    int countLinks;

    Page** pages = (Page**) malloc(sizeof(Page*) * countPages);
    int i = 0;

    for (i = 0; i < countPages; i++) {
        getline(&line, &len, graph);

        token = strtok(line, " ");
        strcpy(nome, token);

        token = strtok(NULL, " ");
        countLinks = atoi(token);
        token = strtok(NULL, " ");

        Page* page = newPage(nome, countLinks);

        for (int j = 0; j < countLinks; j++) {
            page->links[j] = createString(token);
            token = strtok(NULL, " ");
        }
        pages[i] = page;
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

Page* newPage(char* nome, int countLinks){
    Page* page = (Page*)malloc(sizeof(Page));
    page->nome = createString(nome);
    page->countLinks = countLinks;
    page->links = (String**)malloc(sizeof(String*)*countLinks);
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

