#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../exo2/liste.h"
#include "fichier.h"

List listdir(char* root_dir) {
    //Création de la liste contenant le résultat:
    List liste_fics = initList();

    //Allocation de la liste
    DIR* dp = opendir(root_dir);
    struct dirent *ep;

    if(dp != NULL) {
        while((ep = readdir(dp)) != NULL) {
            Cell* new = buildCell(ep->d_name);
            insertLast(liste_fics, new);
        }
    }
    closedir(dp);
    return liste_fics;
}

int file_exists(char* file) {
    List maListe = listdir(file);
    if(searchList(maListe, file) == NULL) return 0;
    return 1;
}

void cp(char* to, char* from) {
    if(file_exists(to)) {
        
    }
}
    
