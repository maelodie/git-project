#ifndef _GIT_
#define _GIT_
#include "ref.h"
#include "commit.h"
#include "worktree.h"
#include "fichier.h"
#include "hash.h"

//Cette fonction ajoute un fichier/repertoire dans le worktree correspondant au stage
void myGitAdd(char* file_or_folder);

//Cette fonction affiche le contenu de la zone de préparation
void listAdd();

//Cette fonction cree un point de sauvegarde (comme git commit)
void myGitCommit(char* branch_name, char* message);

#endif