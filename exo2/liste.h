#ifndef _LISTE_
#define _LISTE_

/*
    Ce type de donnée est une liste chaînée avec un champ
    data qui contient une chaîne de caractères 
*/
typedef struct cell {
    char* data;
    struct cell* next;
} Cell;

typedef Cell* List; //List est un Alias de Cell*

//Initialise une liste vide
List initList();

//Alloue et retourne une cellule de la liste 
Cell* buildCell(char* ch);

//Ajoute un élément en tête de liste
void insertFirst(List L, Cell* C);

//Ajoute un élément en fin de liste
void insertLast(List L, Cell* C);

//Affiche la liste chaînée
void printList(List L);

//Désalloue la mémoire d'une cellule
void freeCell(Cell* C);

//Désalloue la mémoire d'une liste
void freeList(List L);

//Retourne la chaîne de caractère représentée
char* ctos(Cell* c);

//Transforme la liste en chaîné de caractères
char* ltos(List L);

//Renvoie le i-ème élément d'une liste 
Cell* listGet(List L, int i);

//Recherche un élément dans une liste à partir de son contenu
//Renvoie une référence sur l'élément ou NULL si l'élément n'est pas dans la liste
Cell* searchList(List L, char* str);

//Permet de transformer une chaîné de caractères représentant une liste en 
//Une liste chaînée
List stol(char*s);

//Ecrit une liste dans un fichier
void ltof(List L, char* path);

//Lit une liste enregistrée dans un fichier
List ftol(char* path);


#endif