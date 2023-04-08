#define MY_PATH "/home/maeva/"
#include "liste.h"

#ifndef _FICHIERS_

//Cette fonction crée une liste contenant le nom des fichiers et répertoire de root_dir
List* listdir(char* root_dir);

//Cette fonction vérifie que le fichier existe dans le directory
int file_exists(char* file);

//Cette fonction copie le contenu d'un fichier vers une autre 
void cp(char* to, char* from);

//Cette fonction retourne le chemin d'un fichier à partir de son hash
char* hashToPath(char* hash);

//Cette fonction crée un instantané du fichier en paramètres
void blobFile(char* file);
#endif 