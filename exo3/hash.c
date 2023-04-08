#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hash.h"

int hashFile(char * source, char * dest) {
    char cmd[1000];
    sprintf(cmd, "cat %s | sha256sum > %s", source, dest);
    system(cmd);
    return 0;
}

char* sha256file(char* file) {
    char* res = (char*)malloc(sizeof(char)*65); //valeur du hash

    //ouverture d'un fichier temporaire
    static char template[] = "/tmp/hashXXXXXXX";
    char fname[1000];
    strcpy(fname, template);
    int fd = mkstemp (fname);
    printf("Descripteur des fichiers ouverts: %d\n", fd);

    //Hashage
    hashFile(file, fname);

    //Récupération de la valeur dans fname
    FILE* f = fopen(fname, "r");
    if(f==NULL) {
        return NULL;
    }
    fscanf(f, "%s", res);
    fclose(f);

    //Retour
    return res;

}