#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

int main(int argc, char* argv[]) {
    //Initialisation de la liste
    List L = initList();

    //Construction de cellule
    Cell* c1 = buildCell("Hello");
    Cell* c2 = buildCell("MyFriend");
    Cell* c3 = buildCell("How");
    Cell* c4 = buildCell("Are");
    Cell* c5 = buildCell("You");
    Cell* c6 = buildCell("Today");

    //Chaînage
    insertLast(L, c4);
    insertFirst(L, c5);
    insertLast(L, c6);
    printList(L);
    
    //Désallocation des cellules
    freeCell(c1);
    freeCell(c2);
    freeCell(c3);
    freeList(L);
    return 0;
}