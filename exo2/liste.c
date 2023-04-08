#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

List* initList() {
    List* new = malloc(sizeof(List));
    *new = NULL;
    return new;
}

void listeVide(List* L) {
    if((*L) == NULL) {
        printf("La liste est vide\n");
    }
}

Cell* buildCell(char* ch) {
    Cell* new = (Cell*)malloc(sizeof(Cell));
    new->data = strdup(ch);
    new->next = NULL;
    return new;
}

void insertFirst(List* L, Cell* C) {
    C->next = *L;
    *L = C;
}

void printCell(Cell* C) {
    printf("%s\n",C->data);
    
}

void printList(List* L) {
    List ptr = *L;
    while((ptr)) {
        printf("%s ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void freeCell(Cell* C) {
    free(C->data);
    free(C);
}

void freeList(List* L) {
    if((*L)!=NULL) {
        Cell* toDelete = (*L);
        while(*L) {
            toDelete = (*L);
            (*L) = (*L)->next;
            freeCell(toDelete);
        }
    }
    free(L);
    
}

char* ctos(Cell* c) {
    return c->data;
}

char* ltos(List* L) {
    if(L == NULL) {
        return " ";
    }
    char* ch = (char*)malloc(MAX_FILES*sizeof(char));
    List ptr = *L;
    while(ptr != NULL) {
        strcat(ch, ctos(ptr));
        ptr = ptr->next;
        if(ptr != NULL) {
            strcat(ch, "|");
        }
    }
    return ch;
}

Cell* listGet(List *L, int i) {
    int pos = 0;
    List ptr = *L;
    
    while(ptr && pos!=i) {
        ptr = ptr->next;
        pos++;
    }

    if(ptr == NULL) {
        printf("INDEX_OUT_OF_RANGE\n");
    }
    return ptr;
}

Cell* searchList(List* L, char* str) {
    List ptr = *L;
    while(ptr && strcmp(ptr->data,str)!=0) {
        ptr = ptr->next;
    }
    return ptr;
}


List* stol(char* s){
    List* L = initList();
    Cell* courant = NULL;
    char* deb = s;
    char* fin = s;
    while (*fin != '\0'){
        if (*fin == '|'){
            Cell* c = buildCell(strndup(deb, fin - deb));
            if (courant != NULL){
                courant->next = c;
            }
            else{
                *L = c;
            }
            courant = c;
            deb = fin + 1;
        }
        fin++;
    }
    if (deb != fin){
        Cell* c = buildCell(strndup(deb, fin - deb));
        if (courant != NULL){
            courant->next = c;
        }
        else{
            *L = c;
        }
    }
    return L;
}


void ltof(List* L, char* path) {
    FILE* f = fopen(path,"w");
    if(f == NULL) {
        printf("Erreur sur l'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }
    Cell* xs = *L;
    while(xs) {
        fprintf(f,"%s\n",xs->data);
        xs = xs->next;
    }
    fclose(f);
}

List* ftol(char* path) {
    List* L = initList();

    FILE* f = fopen(path,"r");
    if(f == NULL) {
        printf("Erreur sur l'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    char buffer[400];
    while(fgets(buffer, 400, f)) {
        insertFirst(L, buildCell(strdup(buffer)));
    }

    fclose(f);
    return L;
}