#ifndef _COMMIT_
#define _COMMIT_
#define Ncommit 30

#include "commit.h"
#include "fichier.h"
#include "hash.h"

typedef struct key_value_pair {
    char* key;
    char* value;
} kvp;

typedef struct hash_table {
    kvp** T;
    int n; 
    int size;
} HashTable;

typedef HashTable Commit;

//Cette fonction permet d'allouer et d'initialiser un element kvp
kvp* createKeyVal(char* key, char* val);

//Cette fonction permet de désallouer un element kvp
void freeKeyVal(kvp* kv);

//Cette fonction permet de convertire un élément en une chaîne de caractère
//cle: valeur
char* kvts(kvp* k);

//Cette fonction permet de convertir une chaine en kvp
kvp* stkv(char* str);

//Cette fonction alloue et initialise un Commit avec une taille 
Commit* initCommit();

//Ma fonction de hachage
unsigned long hash(unsigned char * str);

//Cette fonction insère la paire (key, value) dans la table
void commitSet(Commit* c, char* key, char* value);

//Cette fonction alloue, initialise et ajoute l'élément obligatoire 
//correspondant à la clé "tree" 
Commit* createCommit(char* hash);

//Cette fonction cherche dans la table s'il existe un élément dont la clé
//est key 
char* commitGet(Commit* c, char* key);

//Cette fonction convertit un commit en une chaine
char* cts(Commit* c);

//Cette fonction convertit une chaine en un commit
Commit* stc(char* ch);

//Cette fonction convertit un commit en file
void ctf(Commit* c, char* file);

//Cette foncion convertit un file en un commit
Commit* ftc(char* file);

//Cette fonction réalise un enregistrement instantané d'un Commit
char* blobCommit(Commit* c);

//Cette fonction retourne le chemin vers un commit
char* hashToPathCommit(char* hash);
#endif