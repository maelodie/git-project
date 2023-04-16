#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "branch.h"

int main(void) {
    //Tests fonctions de base
    initBranch();
    printf("%d\n",branchExists("maBranche"));
    //createBranch("hello");
    printf("%s\n",getCurrentBranch());

    //Tests print a retester
    printBranch("maBranche");

    //Test Liste
    List* L = branchList("maBranche");
    printList(L);

    List* L2 = getAllCommits();
    printList(L2);

    return 0;
}