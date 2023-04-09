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

char* wtfs(WorkFile* wf) {
    char* res = (char*)malloc(sizeof(char)*1000);
    sprintf(res,"%s\t%s\t%d", wf->name, wf->mode, wf->name);
    return res;
}

WorkFile* stwf(char* ch) {
    char* name = (char*)malloc(sizeof(char)*100);
    char* hash = (char*)malloc(sizeof(char)*100);
    int mode;
    sscanf(ch,"%s\t%s\t%d", name, hash, mode);
    WorkFile res = createWorkFile(name);
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
    int pos = 0;
    for(int i = 0; i < (wt->size); i++) {
        if((wt->tab[i]).name == name) return i;
    }
    return -1;
}

int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode) {
    if(inWorkTree(name) > -1) {
        printf("Existe déjà\n");
        return -1;
    }
    if()
}
