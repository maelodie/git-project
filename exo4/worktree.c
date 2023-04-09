#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worktree.h"

WorkFile* createWorkFile(char* name) {
    WorkFile* new = (WorkFile*)malloc(sizeof(WorkFile));
    new->name = name;
    new->hash = NULL;
    new->mode = 0;
    return new;
}

void printWorkFile(WorkFile* wf) {
    printf("nom: %s\nhash: %s\nmode: %d\n", wf->name, wf->hash, wf->mode);
}
char* wtfs(WorkFile* wf) {
    char* res = (char*)malloc(sizeof(char)*1000);
    sprintf(res,"%s\t%s\t%d", wf->name, wf->hash, wf->mode);
    return res;
}

WorkFile* stwf(char* ch) {
    char* name = (char*)malloc(sizeof(char)*100);
    char* hash = (char*)malloc(sizeof(char)*100);
    int mode;
    sscanf(ch,"%s\t%s\t%d", name, hash, &mode);
    WorkFile* res = createWorkFile(name);
    res->hash = hash;
    res->mode = mode;
    return res;
}

WorkTree* initWorkTree() {
    WorkTree* new = (WorkTree*)malloc(sizeof(WorkTree));
    new->tab = (WorkFile*)malloc(sizeof(WorkFile)*W_MAX);
    new->size = W_MAX;
    new->n = 0;
    return new;
}

int inWorkTree(WorkTree* wt, char* name) {
    for(int i = 0; i < (wt->size); i++) {
        if((wt->tab[i]).name == name) {
            return i;
        }
    }
    return -1;
}

int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode) {
    if(inWorkTree(wt, name) > -1) {
        printf("Existe déjà\n");
        return -1;
    }
    if(wt->size > wt->n) {
        wt->tab[wt->n].name = strdup(name);
        wt->tab[wt->n].mode = mode;
        if(hash != NULL) {
            wt->tab[wt->n].hash = strdup(hash);
        }
        else {
            wt->tab[wt->n].hash = NULL;
        }
        (wt->n)++;
        return 0;
    }
    else {
        printf("Le tableau est rempli\n");
        return -1;
    }
}

void printWorkTree(WorkTree* wt) {
    for(int i = 0; i < wt->n; i++) {
        printWorkFile(&(wt->tab[i]));
    }
}

char* wtts(WorkTree* wt) {
    char* res = (char*)malloc(sizeof(char)*1000);
    char* tabVal;
    char* sep = "\n";
    for(int i = 0; i < wt->n; i++) {
        tabVal = wtfs(&(wt->tab[i]));
        strcat(res, tabVal);
        strcat(res, sep);
    }
    return res;
}


WorkTree* stwt(char* ch) {
    WorkTree* res = initWorkTree();
    char* fin = ch;
    char* deb = ch;
    char* workfile;
    WorkFile* wf;
    while(*fin != '\0') {
        if(*fin == '\n') {
            workfile = strndup(deb, fin - deb);
            wf = stwf(workfile);
            appendWorkTree(res, wf->name, wf->hash, wf->mode);
            deb = fin + 1;
        }
        fin++;
    }
    return res;
}

int wttf(WorkTree* wt, char* file) {
    FILE* f = fopen(file, "w");
    if(f) {
        fprintf(f, "%s", wtts(wt));
        fclose(f);
        return 0;
    }
    return -1;
}

WorkTree* ftwt(char* file) {
    FILE* f = fopen(file, "r");
    char* buffer = (char*)malloc(sizeof(char)*1000);
    char* res = (char*)malloc(sizeof(char)*1000*W_MAX);
    while(fgets(buffer, W_MAX, f)) {
        strcat(res, buffer);
    }
    return stwt(res);
}

void freeWorkFile(WorkFile* wf) {
    free(wf);
}

void freeWorkTree(WorkTree* wt) {
    free(wt->tab);
    free(wt);
}
