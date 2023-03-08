#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

List initList() {
    List new = (List)malloc(sizeof(List));
    return new;
}

Cell* buildCell(char* ch) {
    Cell* new = (Cell*)malloc(sizeof(Cell));
    new->data = strdup(ch);
    new->next = NULL;
    return new;
}

void insertFirst(List L, Cell* C) {
    C->next = L;
    L = C;
}

void insertLast(List L, Cell* C) {
    if(L == NULL) {
        L = C;
    }

    List xs = L;
    while(xs->next) {
        xs = xs->next;
    }
    xs->next = C;

}

void printList(List L) {
    List xs = L;
    while(xs) {
        printf("%s ",xs->data);
        xs = xs->next;
    }
    printf("\n");
}

void freeCell(Cell* C) {
    free(C->data);
    free(C);
}

void freeList(List L) {
    List toDelete = L;
    while(L) {
        toDelete = L;
        L = L->next;
        freeCell(toDelete);
    }
}

char* ctos(Cell* c) {
    return c->data;
}

char* ltos(List L) {
    char* res='\0';
    List xs = L;
    while(xs->next) {
        strcat(res,strcat(ctos(xs),"|" ));
        xs = xs->next;
    }
    strcat(res,L->data);
    return res;
}

Cell* listGet(List L, int i) {
    int pos = 0;
    List xs = L;
    
    while(xs && pos!=i) {
        xs = xs->next;
        pos++;
    }

    return xs;
}

Cell* searchList(List L, char* str) {
    List xs = L;
    while(xs && strcmp(L->data,str)==0) {
        xs = xs->next;
    }
    return xs;
}

List stol(char* s) {
    List L = initList();

    char* cellule = '\0';
    int i = -1;

    while(s[i]!='\0') {
        i++;
        if(s[i]=='|') {
            insertLast(L,buildCell(cellule));
            cellule[0]='\0';

        }
        else if(s[i]=='\0') {
            insertLast(L,buildCell(cellule));
        }
        else {
            strcat(cellule,&s[i]);
        }
    }
    return L;
}

void ltof(List L, char* path) {
    FILE* f = fopen(path,"w");
    if(f == NULL) {
        printf("Erreur sur l'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }
    List xs = L;
    while(xs) {
        fprintf(f,"%s\n",xs->data);
        xs = xs->next;
    }
    fclose(f);
}

List ftol(char* path) {
    List L = initList();

    FILE* f = fopen(path,"r");
    if(f == NULL) {
        printf("Erreur sur l'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    char buffer[400];
    while(fgets(buffer, 400, f)) {
        insertLast(L, buildCell(strdup(buffer)));
    }

    fclose(f);
    return L;
}












