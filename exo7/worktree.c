#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "worktree.h"
#include "fichier.h"
#include "hash.h"

WorkFile* createWorkFile(char* name) {
    WorkFile* new = (WorkFile*)malloc(sizeof(WorkFile));
    new->name = name;
    new->hash = NULL;
    new->mode = 0;
    return new;
}

void printWorkFile(WorkFile* wf) {
    printf("nom: %s\nhash: %s\nmode: %d\n", wf->name, wf->hash, wf->mode);
}

char* wtfs(WorkFile* wf) {
    char* res = (char*)malloc(sizeof(char)*1000);
    sprintf(res,"%s\t%s\t%d", wf->name, wf->hash, wf->mode);
    return res;
}

WorkFile* stwf(char* ch) {
    char* name = (char*)malloc(sizeof(char)*100);
    char* hash = (char*)malloc(sizeof(char)*100);
    int mode;
    sscanf(ch,"%s\t%s\t%d", name, hash, &mode);
    WorkFile* res = createWorkFile(name);
    res->hash = hash;
    res->mode = mode;
    return res;
}

WorkTree* initWorkTree() {
    WorkTree* new = (WorkTree*)malloc(sizeof(WorkTree));
    new->tab = (WorkFile*)malloc(sizeof(WorkFile)*W_MAX);
    new->size = W_MAX;
    new->n = 0;
    return new;
}

int inWorkTree(WorkTree* wt, char* name) {
    for(int i = 0; i < wt->n; i++) {
        if(strcmp(wt->tab[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode) {
    if(inWorkTree(wt, name) > -1) {
        printf("Existe déjà\n");
        return -1;
    }
    if(wt->size > wt->n) {
        wt->tab[wt->n].name = strdup(name);
        wt->tab[wt->n].mode = mode;
        if(hash != NULL) {
            wt->tab[wt->n].hash = strdup(hash);
        }
        else {
            wt->tab[wt->n].hash = NULL;
        }
        (wt->n)++;
        return 0;
    }
    else {
        printf("Le tableau est rempli\n");
        return -1;
    }
}

void printWorkTree(WorkTree* wt) {
    for(int i = 0; i < wt->n; i++) {
        printWorkFile(&(wt->tab[i]));
    }
}

char* wtts(WorkTree* wt) {
    char* res = (char*)malloc(sizeof(char)*1000);
    char* tabVal = (char*)malloc(sizeof(char));
    char* sep = "\n";
    for(int i = 0; i < wt->n; i++) {
        tabVal = wtfs(wt->tab + i);
        strcat(res, tabVal);
        strcat(res, sep);
    }
    return res;
}

WorkTree* stwt(char* ch) {
    WorkTree* res = initWorkTree();
    char* fin = ch;
    char* deb = ch;
    char* workfile;
    WorkFile* wf;
    while(*fin != '\0') {
        if(*fin == '\n') {
            workfile = strndup(deb, fin - deb);
            wf = stwf(workfile);
            appendWorkTree(res, wf->name, wf->hash, wf->mode);
            deb = fin + 1;
        }
        fin++;
    }
    return res;
}

int wttf(WorkTree* wt, char* file) {
    FILE* f = fopen(file, "w");
    if(f) {
        fprintf(f, "%s", wtts(wt));
        fclose(f);
        return 0;
    }
    return -1;
}

WorkTree* ftwt(char* file) {
    FILE* f = fopen(file, "r");
    if(f == NULL) {
        printf("l'ouverture de f a échoué\n");
        exit(EXIT_FAILURE);
    }
    char* buffer = (char*)malloc(sizeof(char)*1000);
    char* res = (char*)malloc(sizeof(char)*1000*W_MAX);
    while(fgets(buffer, W_MAX, f)) {
        strcat(res, buffer);
    }
    return stwt(res);
}

void freeWorkFile(WorkFile* wf) {
    free(wf);
}

void freeWorkTree(WorkTree* wt) {
    free(wt->tab);
    free(wt);
}

char* blobWorkTree(WorkTree* wt) {
    //Création du fichier temporaire
    char fname[100] = "/tmp/worktreeXXXXXX";
    int fd = mkstemp(fname); //Création + descripteur de fichier ouvert
    if(fd == -1) {
        printf("mkstemp a échoué\n");
        exit(EXIT_FAILURE);
    }
    //Ecriture de la représentation du worktree
    wttf(wt, fname);
    //WorkTree* wt2 = ftwt(fname);
    //printWorkTree(wt2);

    ///Copie vers l'instantane
    char* hash = sha256file(fname);
    char* path = hashToFile(hash); //crée un dossier et retourne le chemin vers le fichier
    
    //Ajout du nombre de cases mémoire pour path (pour ajouter .c)
    size_t path_len = strlen(path);
    size_t total_len = path_len + strlen(".t") + 1;
    char* full_path = malloc(total_len);
    strcpy(full_path, path);
    strcat(full_path, ".t");
    cp(full_path, fname); //copie du contenu de fname vers path

    return hash;
}

char* saveWorkTree(WorkTree* wt, char* path) {
    for(int i = 0; i < wt->n; i++) {
        char* current_path = concat_paths(path, wt->tab[i].name);
        //Si le path est un fichier, on crée un instantané du fichier et on change les données dans Worktree
        if(isFile(current_path) == 1) {
            blobFile(current_path);
            wt->tab[i].hash = sha256file(current_path);
            wt->tab[i].mode = getChmod(current_path);
        }
        //Si le path est un dossier, on crée une nouvelle worktree avec son contenu, puis on fait un appel récursif
        else {
            WorkTree* wt2 = initWorkTree();
            List* L = listdir(current_path);
            for(Cell* c = *L; c != NULL; c = c->next) {
                //fichiers cachés
                if(c->data[0] == '.') 
                    continue;
                appendWorkTree(wt2, c->data, sha256file(c->data), 0);
            }
            wt->tab[i].hash = saveWorkTree(wt2, current_path);
            wt->tab[i].mode = getChmod(current_path);
        }
    }
    return blobWorkTree(wt);
}

int isWorkTree(char* hash) {
    if(file_exists(strcat(hashToPath(hash),".t"))) {
        return 1; //cas d'un repertoire
    }
    if(file_exists(hashToPath(hash))) {
        return 0; //cas d'un fichier
    }
    return -1; //fichier non existant
}

void restoreWorkTree(WorkTree* wt, char* path) {
    for(int i=0; i < wt->n; i++) {
        char* restored = concat_paths(path, wt->tab[i].name); //path du workfile
        char* instantane = hashToPath(wt->tab[i].hash); //copie du chemin du workfile
        char* hash = wt->tab[i].hash;

        if(isWorkTree(hash) == 0) {
            cp(restored, instantane);
            setMode(getChmod(instantane), restored);
        }
        else if(isWorkTree(hash) == 1) {
            strcat(instantane, ".t");
            WorkTree* new_wt = ftwt(instantane);
            restoreWorkTree(new_wt, restored);
            setMode(getChmod(instantane), restored);
        }
    }
}