#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worktree.h"
#include "fichier.h"
#include "liste.h"
#include "hash.h" 

int main(void) {
    //Création d'un WorkTree
    WorkTree* wt = initWorkTree();
    
    //Import d'une liste représentant le répertoire
    List* L = listdir(".");
    for(Cell* c = *L; c != NULL; c = c->next) {
        if(c->data[0] == '.') {
            continue;
       }
        appendWorkTree(wt, c->data, sha256file(c->data), getChmod(concat_paths(".", c->data)));
    }

    //Test des fonctions
    //blobWorkTree(wt);
    //saveWorkTree(wt, ".");
    restoreWorkTree(wt,".");
    //Fonctions de libération
    freeList(L);
    freeWorkTree(wt);
    return 0;
}