#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ref.h"


void initRefs() {
    if(!file_exists(".refs")) {
        system("mkdir .refs");
        system("touch .refs/master");
        system("touch .refs/HEAD");
    }
}

void createUpdateRef(char* ref_name, char* hash) {
    char cmd[256];
    sprintf(cmd, "echo %s > .refs/%s", hash, ref_name);
    system(cmd);
}

void deleteRef(char* ref_name) {
    char file[50];
    char cmd[256];
    sprintf(file, ".refs/%s", ref_name);

    if(!file_exists(file)) {
        printf("la référence %s n'existe pas\n", ref_name);
    }
    else {
        sprintf(cmd, "rm -f %s ", file);
        system(cmd);
    }
}

char* getRef(char* ref_name) {
    char* res = (char*)malloc(sizeof(char)*256);
    char file[255];
    sprintf(file, ".refs/%s" , ref_name);

    if(!file_exists(file)) {
        printf("Cette référence n'existe pas\n");
        return NULL;
    }

    FILE* f = fopen(file, "r");
    if(f == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }

    fgets(res, 256, f);
    res[strcspn(res, "\n")] = '\0'; //enlève le \n de fgets et remplace par \0
    fclose(f);

    return res;
}

void listRefs() {
    if(file_exists(".refs")) {
        printf("REFS : \n");
        printf("(Référence : contenu)\n");
        List* L = listdir(".refs");
        for(Cell* ptr = *L; ptr != NULL; ptr = ptr->next) {
            if(ptr->data[0] == '.')
                continue; //On ne liste pas les fichiers cachés
            char* content = getRef(ptr->data);
            printf("%s : %s\n", ptr->data, content);
        }
    }
    else {
        printf(".refs n'existe pas. Veuillez initialiser les références avec initRefs()\n");
    }
}