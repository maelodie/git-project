#ifndef _BRANCH_
#define _BRANCH_
#include "commit.h"
#include "ref.h"
#include "fichier.h"
#include "liste.h"

//Cette fonction crée le fichier caché .current_branch
void initBranch();

//Cette fonction vérifie l'existence d'une branche
int branchExists(char* branch);

//Cette fonction crée une référence branch
void createBranch(char* branch);

//Cette fonction lit le contenu de .current_branch
char* getCurrentBranch();

//Cette fonction parcourt la branche <branch> et
//pour chacun de ses commits affiche son hash et son message descriptif
void printBranch(char* branch);

//Cette fonction retourne une liste chainée contenant le hash de tous les
//commits de la branche
List* branchList(char* branch);

//Cette fonction renvoie la liste des hash des commits de 
//Toutes les branches
List* getAllCommits();

#endif 