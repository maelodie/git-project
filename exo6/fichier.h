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

//Cette fonction crée un dossier à partir du hash en paramètre
char* hashToFile(char* hash);

//Cette fonction concatène les deux chemins en paramètre
char* concat_paths(char* path1, char* path2);

//Cette fonction retourne si le path en paramètre est un fichier
int isFile(char* path);

//Cette fonction récupère le niveau de permission d'un fichier
int getChmod(const char* path);

//Cette fonction modifie les autorisations
void setMode(int mode, char* path);
#endif 