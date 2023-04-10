#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "liste.h"
#include "fichier.h"
#include "hash.h"

List* listdir(char* root_dir) {
    //Création de la liste contenant le résultat:
    List* liste_fics = initList();
    Cell* new;
    //Allocation de la liste
    DIR* dp = opendir(root_dir);
    struct dirent *ep;

    if(dp != NULL) {
        while((ep = readdir(dp)) != NULL) {
            new = buildCell(ep->d_name);
            insertFirst(liste_fics, new);
        }
    }
    closedir(dp);
    return liste_fics;
}

int file_exists(char* file) {
    List* maListe = listdir(".");
    if(searchList(maListe, file) == NULL) return 0;
    return 1;
}

void cp(char* to, char* from) {
    if(file_exists(from)) {
        char ligne [256];
        FILE* source = fopen(from, "r") ;
        FILE* dest = fopen(to, "w") ;
        while (fgets (ligne, 256, source)) {
            fputs(ligne, dest);
        }
        fclose(dest);
        fclose(source);
    }
}
    
char* hashToPath(char* hash) {
    char* path = (char*)malloc(sizeof(char)*(strlen(hash)+1));
    path[0] = hash[0];
    path[1] = hash[1];
    path[2] = '/';
    int i;
    for(i = 3; i <= strlen(hash); i++) {
        path[i] = hash[i-1];
    }
    path[i] = '\0';
    return path;
}

void blobFile(char* file) {
    char* hash = sha256file(file);
    char* folder = strdup(hash);
    folder[2] = '\0';
    if(!file_exists(folder)) {
        char buffer[100];
        sprintf(buffer, "mkdir %s", folder);
        system(buffer);
    }
    char* newFile = hashToPath(hash);
    cp(newFile, file);
}


