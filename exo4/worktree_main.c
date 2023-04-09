#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worktree.h"

void sep() {
    printf("_______________________________________________\n");
}

int main(void) {
    //Création de workfiles
    WorkFile* wf1 = createWorkFile("mondoc1");
    WorkFile* wf2 = createWorkFile("mondoc2");
    WorkFile* wf3 = createWorkFile("mondoc3");
    WorkFile* wf4 = createWorkFile("mondoc4");

    //Affichage
    printWorkFile(wf1);
    printWorkFile(wf2);
    printWorkFile(wf3);
    printWorkFile(wf4);
    sep();

    //Conversion d'un workfile en une chaine
    printf("%s\n",wtfs(wf1));
    sep();
    
    //Conversion d'une chaine en un Workfile
    WorkFile* wf5 = stwf("mondoc sk34zf134141ffdaaf 2");
    printWorkFile(wf5);
    sep();


    //Initialisation d'un WorkTree
    WorkTree* wt = initWorkTree();
    appendWorkTree(wt, "dossier1", "dfqdlkqjf1431431", 2);
    appendWorkTree(wt, "dossier2", "qdfqdf42fq341341", 1);
    appendWorkTree(wt, "dossier3", "aiaeraerfkdjld13", 2);
    appendWorkTree(wt, "dossier4", "fdsflkjfoinq1341", 4);

    //Affichage d'un WorkTree
    printWorkTree(wt);
    sep();

    //Création d'un worktree à partir d'une chaine 
    char* ch = "doc1 dflkqjdflkqj141dsfq 1\ndoc2 fqdjfq134fdfqfdqfdf 3\ndoc3 dqjkfqjdfqkjdf13414 2";
    WorkTree* wt2 = stwt(ch);
    printWorkTree(wt2);
    sep();
    
    //Input des données dans un file
    wttf(wt, "file.txt");

    //Création d'un WorkTree à partir d'un file
    WorkTree* wt3 = ftwt("file.txt");
    printWorkTree(wt3);

    //Désallocation des données
    freeWorkFile(wf1);
    freeWorkFile(wf2);
    freeWorkFile(wf3);
    freeWorkFile(wf4);
    freeWorkFile(wf5);
    freeWorkTree(wt);
    freeWorkTree(wt2);
    freeWorkTree(wt3);

    return 0;
}