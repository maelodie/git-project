#ifndef _BRANCH_
#define _BRANCH_
#include "commit.h"
#include "ref.h"
#include "worktree.h"
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

//Cette fonction permet de restaurer le worktree associé à
//un commit dont le hash est donné en paramètre
void restoreCommit(char* hash_commit);

//Bascule d'une branche à une autre
void myGitCheckoutBranch(char* branch);

//Retourne une nouvelle liste contenant uniquement les élément de L qui 
//Commencent par la chaîne pattern
List* filterList(List* L, char* pattern);

//Permet de revenir sur n'importe quelle version du projet
void myGitCheckoutCommit(char* pattern);

#endif 