#include "page.h"
#include "string.h"
#include "utils.h"

struct page {
    char* nome;
    int countLinks;
    String** links;
};

Page** createPages(char* path,int countPages){
    char* line = (char*) malloc(sizeof(char)*100);
    size_t len = 0;
    removeNewLine(path);
    FILE* graph = fopen(path, "r");
    

    char* token;
    char* nome;
    int countLinks;

    Page** pages = (Page**)malloc(sizeof(Page*)*countPages);
    int i = 0;
    
    for(i = 0; i < countPages; i++){
        getline(&line, &len, graph);
        
        
        token = strtok(line, " ");
        strcpy(nome, token);
      
        token = strtok(NULL, " ");
        countLinks = atoi(token);
        token = strtok(NULL, " ");

        // printf("%s - countlinks: %d : ", nome, countLinks);
        
        Page* page = newPage(nome, countLinks);
        
        for(int j = 0; j < countLinks; j++){
            page->links[j] = createString(token);
            token = strtok(NULL, " ");
        }
        pages[i] = page;
        // printf("i: %d ; nome 0: %s\n", i, getNome(pages[i]));
    }
    fclose(graph);
    return pages;

}

char* getNome(Page* page){
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
    page->nome = strdup(nome);
    page->countLinks = countLinks;
    page->links = (String**)malloc(sizeof(String*)*countLinks);
    return page;
}

void freePage(Page* page){
    free(page->nome);
    free(page->links);
    free(page);
}

