#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "liste.h"
#include "fichier.h"

int main(int argc, char** argv) {
    List* maListe = listdir("/home/maeva/LU2IN006/git-project");
    printList(maListe);
    if(file_exists("liste.h")) {
        printf("Le fichier  existe\n");
    }
    cp("new.txt","helloworld.txt");
    char* path = hashToPath("50dee4dd09d048a3f8d65dc9820a212526d30c6d3c2e4c98c417cefd81b2a650");
    printf("%s\n", path);
    blobFile("new.txt");
    return 0;
}