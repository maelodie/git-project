#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "fichier.h"

void afficher_docs(char* dir) {
    //Allocation de la structure dir
    DIR* dp;
    struct dirent *ep;
   /* char buffer[256];
    strcpy(buffer, dir);*/
    dp = opendir(dir);
    if(dp == NULL) {
        printf("L'allocation de dp a échoué\n");
    }

    //Lecture des fichiers 
    if(dp != NULL) {
        while((ep = readdir(dp)) != NULL) {
            //ep = readdir(dp);
            printf("%s \n", ep->d_name);
        }
    }
    closedir(dp);
}

int main(void) {
    afficher_docs(MY_PATH);
    return 0;
}