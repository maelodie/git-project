#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
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
    /*
    List* maListe = listdir(".");
    if(searchList(maListe, file) == NULL) return 0;
    return 1;
    */
    struct stat st;
    if(stat(file, &st) == -1) return 0;
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
    else {
        printf("Le fichier n'existe pas\n");
    }
}
    
char* hashToPath(char* hash) {
    char* path = (char*)malloc(sizeof(char)*(strlen(hash)+4));
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

char* hashToFile(char* hash) {
    char* folderName = strdup(hash);
    folderName[2] = '\0';
    struct stat st;
    if(stat(folderName, &st) == -1) {
        mkdir(folderName, 0700); //les utilisateurs du groupe ont tous les droits sur le dossier
    }
    return hashToPath(hash);
}

char* concat_paths(char* path1, char* path2) {
    //char* new_path = malloc(strlen(path1) + strlen(path2) + 1);
    char* new_path = (char*)calloc((strlen(path1)+strlen(path2)+1),sizeof(char));
    if(!new_path) {
        printf("l'allocation du nouveau chemin a échoué\n");
        return NULL;
    }
    strcat(new_path, path1);
    strcat(new_path, "/");
    strcat(new_path, path2);
    return new_path;
}

int isFile(char* path) {
    struct stat st;
    //st_mode contient le type du fichier
    //S_IFREG est true si c'est bien un fichier régulier
    if(stat(path, &st) == 0) {
        if(S_ISREG(st.st_mode)) return 1;
    }
    return 0;
}

int getChmod(const char* path) {
    struct stat ret;

    //Retourne -1 si le fichier n'existe pas 
    if(stat(path, &ret) == -1) {
        return -1;
    }

    return (ret.st_mode & S_IRUSR) | (ret.st_mode & S_IWUSR) | (ret.st_mode & S_IXUSR)/*Owner*/ |
            (ret.st_mode & S_IRGRP) | (ret.st_mode & S_IWGRP) | (ret.st_mode & S_IXGRP)/*Groupe*/|
            (ret.st_mode & S_IROTH) | (ret.st_mode & S_IWOTH) | (ret.st_mode & S_IXOTH)/*Other*/;
}

void setMode(int mode, char* path) {
    char buff[100];
    sprintf(buff, "chmod %d %s", mode, path);
    system(buff);
}
