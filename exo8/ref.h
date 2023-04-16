#ifndef _REF_
#define _REF_
#include "commit.h"
#include "fichier.h"
#include "liste.h"
#include "hash.h"

//Cette fonction crée un répertoire caché .refs
void initRefs();

//Cette fonction met a jour une ref en remplacant son contenu par hash
void createUpdateRef(char* ref_name, char* hash);

//Cette fonction supprime une référence
void deleteRef(char* ref_name);

//Cette fonction recupere vers quoi pointe une reference
//Si c'est vide, on retourne une chaine vide
//Si le fichier n'existe pas, on retourne null
char* getRef(char* ref_name);

//Cette fonction affiche toutes les références existantes
void listRefs();
#endif 