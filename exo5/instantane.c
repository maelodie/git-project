#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worktree.h"
#include "fichier.h"

int main(void) {
    //Création d'un WorkTree
    WorkTree* wt = initWorkTree();
    appendWorkTree(wt, "dossier1", "dfqdlkqjf1431431", 2);
    appendWorkTree(wt, "dossier2", "qdfqdf42fq341341", 1);
    appendWorkTree(wt, "dossier3", "aiaeraerfkdjld13", 2);
    appendWorkTree(wt, "dossier4", "fdsflkjfoinq1341", 4);

    //Enregistrement instantané du WorkTree
    blobWorkTree(wt);

    return 0;
}