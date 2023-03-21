#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "liste.h"
#include "fichier.h"

int main(int argc, char** argv) {
    List maListe = listdir("/users/nfs/Etu3/21104443/LU2IN006/git-project-main/exo2");
    printList(maListe);
    if(file_exists("liste.h")) {
        printf("Le fichier  existe\n");
    }
    return 0;
}