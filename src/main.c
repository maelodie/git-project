#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "git.h"

int main(int argc, char* argv[]) {
    //initialise les répertoires de références
    if(strcmp(argv[1], "init") == 0) {
        initRefs();
        initBranch();
    }

    //affiche toutes les références existantes
    if(strcmp(argv[1], "refs-list") == 0) {
        listRefs();
    }

    //Crée la référence argv[2](nom d'une ref) 
    //qui pointe vers le commit argv[3](hash)
    if(strcmp(argv[1], "create-ref") == 0) {
        createUpdateRef(argv[2], argv[3]);
    }

    //Supprime la référence argv[2](nom d'une ref)
    if(strcmp(argv[1], "delete-ref") == 0) {
        deleteRef(argv[2]);
    }

    //Ajoute un ou plusiers fichiers à la zone de préparation
    if(strcmp(argv[1], "add") == 0) {
        for(int i = 2; i < argc; i++) {
            myGitAdd(argv[i]);
        }
    }

    //Affiche le contenu de la zone de préparation
    if(strcmp(argv[1], "list-add") == 0) {
        listAdd();
    }

    //Vide la zone de préparation
    if(strcmp(argv[1], "clear-add") == 0) {
        system("rm -r .add");
    }

    //Effectue un commit sur une branche argv[2] 
    //avec optionnellement un message [-m <message>]
    if(strcmp(argv[1], "commit") == 0) {
        if(argc >= 3) {
            if(argc >= 5 && strcmp(argv[3], "-m") == 0) {
                myGitCommit(argv[2], argv[4]);
            }
            else {
                myGitCommit(argv[2], NULL);
            }
        } 
        else {
            printf("Usage: myGit commit <branch_name> [-m <message>]\n");
            return 1;
        }
    }

    //affiche le nom de la branche courante
    if(strcmp(argv[1], "get-current-branch") == 0) {
        printf("%s\n", getCurrentBranch());
    }

    if(strcmp(argv[1], "branch") == 0) {
        if(!branchExists(argv[2])) {
            createBranch(argv[2]);
        }
        else{
            printf("The branch %s already exists.", argv[2]);
        }
    }

    //Navigue vers la branche en param
    if(strcmp(argv[1], "checkout-branch") == 0) {
        if(!branchExists(argv[2])) {
            printf("The branch %s does not exist.", argv[2]);
        }
        else {
            myGitCheckoutBranch(argv[2]);
        }
    }

    //Restaure la version des commits qui commencent par pattern
    if(strcmp(argv[1], "checkout-commit") == 0) {   
        myGitCheckoutCommit(argv[2]);
    }

    return 0;
}