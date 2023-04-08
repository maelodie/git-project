#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

int main(int argc, char* argv[]) {
    //Initialisation de la liste
    List* L = initList();

    //Construction de cellule
    Cell* c1 = buildCell("Hello");
    Cell* c2 = buildCell("MyFriend");
    Cell* c3 = buildCell("How");
    Cell* c4 = buildCell("Are");
    Cell* c5 = buildCell("You");
    Cell* c6 = buildCell("Today");
    
    listeVide(L);
    //Insertions dans la liste
    insertFirst(L,c6);
    insertFirst(L,c5);
    insertFirst(L,c4);
    insertFirst(L,c3);
    insertFirst(L,c2);
    insertFirst(L,c1);
    printList(L);
    listeVide(L);

    //De liste à chaîne
    printf("%s\n",ctos(c1));
    char* chaine = ltos(L);
    printf("%s\n", chaine);

    //Indice d'une cellule
    Cell* newC = listGet(L, 3);
    printf("%s\n", newC->data);

    //Element d'une liste à partir d'une chaine
    char* chaine2 = "You";
    Cell* newC2 = searchList(L, chaine2);
    printf("%s\n", newC2->data);

    //Chaine vers liste
    char* chaine3 = "Hello|MyFriend|How|Are|You|Today";
    List* L2 = stol(chaine3);
    printList(L2);

    //Test des listes et fichiers
    ltof(L2, "maliste.txt");
    List* L3 = ftol("maliste.txt");
    printList(L3);

    //Désallocation des cellules et de la liste
    freeList(L);
    freeList(L2);
    freeList(L3);
    free(chaine);
    return 0;
}