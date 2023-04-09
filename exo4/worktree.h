#ifndef _WORKTREE_
#define _WORKTREE_
#define W_MAX 20

typedef struct {
    char* name;
    char* hash;
    int mode;
} WorkFile;

typedef struct {
    WorkFile* tab;
    int size; //Taille du tableau
    int n; //Taille du tableau occupée
} WorkTree;

//Manipulation de workfile
//Cette fonction permet de créer un workfile et de l'initialiser
WorkFile* createWorkFile(char* name);

//Affiche les champs du Workfile en argument
void printWorkFile(WorkFile* wf);

//Cette fonction permet de convertir un WorkFile en chaîne de caractères(les champs sont séparés par des tabulations)
char* wtfs(WorkFile* wf);

//Cette fonction permet de convertir une chaîne de caractères en un Workfile
WorkFile* stwf(char* ch);

//Cette fonction permet d'initialiser un WorkTree de taille fixée et de l'initialiser
WorkTree* initWorkTree();

//Cette fonction vérifie la présence d'un fichier ou d'un répertoire dans un worktree
int inWorkTree(WorkTree* wt, char* name);

//Cette fonction ajoute un fichier ou un répertoire au WorkTree
int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode);

//Cette fonction affiche un workTree
void printWorkTree(WorkTree* wt);

//Cette fonction convertit un WorkTree en une chaine de caractères composée des représentations de Workfile
char* wtts(WorkTree* wt);

//Cette fonction convertir une chaine en un WorkTree
WorkTree* stwt(char* ch);

//Cette fonction écrit dans file une chaîne représentant un WorkTree
int wttf(WorkTree* wt, char* file);

//Cette fonction construit un workTree à partir d'un file 
WorkTree* ftwt(char* file);

//Fonctions de désallocation
void freeWorkFile(WorkFile* wf);
void freeWorkTree(WorkTree* wt);

#endif