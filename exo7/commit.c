#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commit.h"
#include "fichier.h"
#include "hash.h"

kvp* createKeyVal(char* key, char* val) {
    kvp* new = (kvp*)malloc(sizeof(kvp));
    new->key = strdup(key);
    new->value = strdup(val);
    return new;
}

void freeKeyVal(kvp* kv) {
    free(kv->key);
    free(kv->value);
    free(kv);
}

char* kvts(kvp* k) {
    char* res = (char*)malloc(sizeof(char)*1000);
    sprintf(res, "%s : %s ", k->key, k->value);
    return res;
}

kvp* stkv(char* str) {
    char key[100], val[100];
    sscanf(str, "%s : %s ", key, val);
    return createKeyVal(key, val);
}

Commit* initCommit() {
    Commit* new = (Commit*)malloc(sizeof(Commit));
    new->size = Ncommit;
    new->T = (kvp**)malloc((new->size)*sizeof(kvp*));
    for(int i = 0; i < new->size; i++) {
        new->T[i] = NULL;
    }
    new->n = 0;
    return new;
}

unsigned long hash(unsigned char *str) {
	unsigned int hash = 0;
	int c = 0;
	while (c == *str++)
	    hash += c;
	return hash;
}

void commitSet(Commit* c, char* key, char* value) {
    int p = hash((unsigned char*)key) % c->size;
    while(c->T[p] != NULL) {
        p = (p+1)%c->size; 
    }
    c->T[p] = createKeyVal(key, value);
    c->n++;
}

Commit* createCommit(char* hash) {
    Commit* new = initCommit();
    commitSet(new, "tree", hash);
    return new;
}

char* commitGet(Commit* c, char* key) {
    int p = hash((unsigned char*)key) % c->size;
    int essai = 0;

    while(c->T[p] != NULL && essai < c->size) {
        if(strcmp(c->T[p]->key, key) == 0) {
            return c->T[p]->value;
        }
        p = (p+1) % c->size;
        essai++;
    }
    return NULL;
}

char* cts(Commit* c) {
    char* res = (char*)calloc(100*c->n, sizeof(char));
    for(int i = 0; i < c->size; i++) {
        if(c->T[i]) {
            strcat(res, kvts(c->T[i]));
            strcat(res,"\n");
        }
    }
    return res;
}

Commit* stc(char* ch) {
    size_t pos = 0;
    size_t n_pos = 0;
    int sep = '\n';
    char* ptr;
    char* result = malloc(sizeof(char)*10000); 
    Commit* c = initCommit(10);
    while (pos < strlen(ch)){
        ptr = strchr(ch + pos, sep); 
        if (ptr == NULL){
            n_pos = strlen(ch)+1;
        }
        else{
            n_pos = ptr - ch + 1;
        }
        memcpy(result, ch+pos, n_pos - pos - 1);
        result[n_pos - pos - 1] = '\0';
        pos = n_pos;
        kvp* elem = stkv(result);
        commitSet(c, elem->key, elem->value);
    }
    return c;
}

void ctf(Commit* c, char* file) {
    FILE* f = fopen(file, "w");
    if(f == NULL) {
        printf("Erreur sur l'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }

    fputs(cts(c), f);
    fclose(f);
}

Commit* ftc(char* file) {
    char buff[256] = "\0";
    char* all = malloc(sizeof(char)*256);
    memset(all, 0, 256);
    FILE* f = fopen(file, "r");
    if (f == NULL){
        printf("ERREUR: ce fichier n'existe pas \n");
        return NULL;
    }

    while (fgets(buff, 256, f) != NULL){
        strcat(all, buff);
    }

    Commit* c = stc(all);
    return c;
}

char* blobCommit(Commit* c) {
    //Création du fichier temporaire
    char fname[100] = "/tmp/commitXXXXXX";
    int fd = mkstemp(fname);
    if(fd == -1) {
        printf("mkstemp a échoué\n");
        exit(EXIT_FAILURE);
    }
    //Ecriture dans fname
    ctf(c, fname);

    //Copie vers l'instantane
    char* hash = sha256file(fname);
    char* path = hashToFile(hash); //crée un dossier et retourne le chemin vers le fichier
    
    //Ajout du nombre de cases mémoire pour path (pour ajouter .c)
    size_t path_len = strlen(path);
    size_t total_len = path_len + strlen(".c") + 1;
    char* full_path = malloc(total_len);
    strcpy(full_path, path);
    strcat(full_path, ".c");
    cp(full_path, fname); //copie du contenu de fname vers path

    return hash;

}