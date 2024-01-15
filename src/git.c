#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "git.h"

void myGitAdd(char* file_or_folder) {
    //Initialisation du Worktree
    WorkTree* wt;
    if(!file_exists(".add")) {
        createFile(".add");
        wt = initWorkTree();
    }
    else {
        wt = ftwt(".add");
    }

    //Ajout d'un fichier dans worktree puis dans .add
    if(file_exists(file_or_folder)) {
        appendWorkTree(wt, file_or_folder, NULL, 0);
        wttf(wt, ".add");
    }
    else {
        printf("le fichier / le répertoire %s n'existe pas\n", file_or_folder);
    }
}

void myGitCommit(char* branch_name, char* message) {
    //existence de .refs
    if(!file_exists(".refs")) {
        printf("il faut d'abord initialiser les références du projet\n");
        return;
    }

    //existence de branch_name
    char file[256];
    sprintf(file, ".refs/%s", branch_name);
    if(!file_exists(file)) {
        printf("La branche n'existe pas\n");
        return;
    }

    //pointeurs dans branch_name et HEAD
    char* last_hash = getRef(branch_name);
    if(last_hash == NULL) {
        printf("le contenu de la branche %s est NULL\n", branch_name);
        return;
    }
    char* head_hash = getRef("HEAD");
    if(head_hash == NULL) {
        printf("le contenu de HEAD est NULL\n");
        return;
    }
    if(strcmp(last_hash, head_hash) != 0) {
        printf("HEAD doit pointer sur le dernier commit de la branche\n");
        return;
    }

    //Charge le Worktree dans .add puis supprime .add
    WorkTree* wt = ftwt(".add");
    if(wt == NULL) {
        printf("Erreur lors du chargement du WorkTree\n");
        return;
    }
    char* hashwt = saveWorkTree(wt, ".");
    system("rm -r .add ");

    //Crée et initialise un commit
    Commit* c = createCommit(hashwt);

    //Ajoute le hash de branch_name comme predecessor de c si branch_name n'est pas vide
    if(strlen(last_hash) !=0) {
        commitSet(c, "predecessor", last_hash);
    }

    //Ajoute un message si le message n'est pas null
    if(message != NULL) {
        commitSet(c, "message", message);
    }

    //Cree un instantane de c et recupere son hash
    char* hashc = blobCommit(c);

    //MAJ branch_name en remplaçant son contenu par hashc
    createUpdateRef(branch_name, hashc);

    //MAJ HEAD en remplaçant son contenu par hashc
    createUpdateRef("HEAD", hashc);
}

void listAdd() {
    if(file_exists(".add")) {
        printf("Zone de préparation:\n");
        WorkTree* wt = ftwt(".add");
        printf("%s\n", wtts(wt));
    }
    else {
        printf("La zone de préparation est vide. Essayez de faire ./myGit add <liste de fichiers>\n");
    }
}