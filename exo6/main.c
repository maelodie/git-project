#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commit.h"
#include "fichier.h"
#include "liste.h"
#include "hash.h"

int main(void) {
    //initialisations
    Commit* c = initCommit();
    commitSet(c, "tree1", "hi");
    commitSet(c, "tree2", "hi");
    commitSet(c, "tree3", "hi");
    commitSet(c, "tree4", "hi");

    //chaine et commit
    char* chaine1 = cts(c);
    Commit *c2 = stc(chaine1);
    commitGet(c2, "tree1"); 
    
    //fichier et commit
    ctf(c, "Commit1.txt");
    Commit* c3 = ftc("Commit1.txt");
    commitSet(c3, "tree5", "hi");

    //blob :)
    blobCommit(c3);
    return 0;
}