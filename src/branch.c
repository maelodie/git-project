#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "branch.h"

void initBranch() {
    FILE* f = fopen(".current_branch", "w"); 
    fputs("master",f);
    fclose(f);
}

int branchExists(char* branch) {
    int branchExists(char* branch);
    List* refs = listdir(".refs");
    return searchList(refs, branch) != NULL;
}

void createBranch(char* branch) {
    char* hash = getRef("HEAD");
    createUpdateRef(branch , hash);
}

char* getCurrentBranch() {
    FILE* f = fopen(".current_branch", "r"); 
    if(f == NULL) {
        printf("Erreur sur l'ouverture de fichier\n");
        return NULL;
    }
    char* branch = (char*)malloc(sizeof(char)*100);
    fscanf(f,"%s",branch);
    fclose(f);
    return branch;
}

void printBranch(char* branch) {
    char* commit_hash = getRef(branch); //recupere vers quoi pointe branche
    Commit* c = ftc(hashToPathCommit(commit_hash)); //commits contenu dans la brache
    
    //Cette fonction parcours les commits tant qu'il y'a un predecessor
    while(c != NULL) {
        if(commitGet(c, "message") != NULL) {
            printf("%s -> %s \n", commit_hash, commitGet(c, "message"));
        } else {
            printf("%s \n", commit_hash);
        }

        if(commitGet(c, "predecessor") != NULL) {
            commit_hash = commitGet(c, "predecessor");
            c = ftc(hashToPathCommit(commit_hash));
        } else {
            c = NULL;
        }
    }
}

List* branchList(char* branch) {
    List* L = initList();
    char* commit_hash = getRef(branch);
    Commit* c = ftc(hashToPathCommit(commit_hash));
    while(c) {
        insertFirst(L, buildCell(commit_hash));
        if(commitGet (c, "predecessor")) {
            commit_hash = commitGet(c, "predecessor");
            c = ftc(hashToPathCommit(commit_hash));
        }
        else {
            c = NULL;
        }
    }
    if(*L == NULL) {
        printf("La liste n'a pas bien été initialisée\n");
    }
    return L;
}

List* getAllCommits() {
    List* L = initList();
    List* contenu = listdir(".refs");

    for(Cell* ptr = *contenu; ptr != NULL; ptr = ptr->next) {
        if(ptr->data[0] == '0')
            continue;
        //liste des commits de la branche pointée par ptr
        List* liste = branchList(ptr->data); 
        //latest commit
        Cell* cell = *liste;
        while(cell) {
            if(searchList(L, cell->data) == NULL) {
                insertFirst(L, buildCell(ptr->data));
            }
            cell = cell->next;
        }  
    }
    return L;
}

void restoreCommit(char* hash_commit) {
    char* commit_path = hashToPathCommit(hash_commit);
    Commit* c = ftc(commit_path);
    char* tree_hash= strcat(hashToPath(commitGet(c, "tree")), ".t");
    WorkTree* wt = ftwt(tree_hash);
    restoreWorkTree(wt, ".");
}

void myGitCheckoutBranch(char* branch) {
    FILE* f = fopen(".current_branch", "w");
    fprintf(f, "%s", branch);
    fclose(f);

    char* hash_commit = getRef(branch);
    createUpdateRef("HEAD", hash_commit);
    restoreCommit(hash_commit);
}

List *filterList(List *L, char *pattern) {
    List *filtered = initList();
    for (Cell *ptr = *L; ptr != NULL; ptr = ptr->next) {
        char *c = strdup(ptr->data);
        c[strlen(pattern)] = '\0';
        if (strcmp(c, pattern) == 0) {
            insertFirst(filtered, buildCell(ptr->data));
        }
        free(c);
    }
    return filtered;
}

void myGitCheckoutCommit(char *pattern) {
    List *L = getAllCommits();
    List *filtred_list = filterList(L, pattern);
    if (listSize(filtred_list) == 1) {
        char *commit_hash = (listGet(filtred_list, 0))->data;
        createUpdateRef("HEAD", commit_hash);
        restoreCommit(commit_hash);
    } else {
        if (listSize(filtred_list) == 0) {
            printf("No pattern matching.\n");
        } else {
            printf("Multiple matchings found:\n");
            for (Cell *ptr = *filtred_list; ptr != NULL; ptr = ptr->next) {
                printf("-> %s\n", ptr->data);
            }
        }
    }
}
