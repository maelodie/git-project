#define MY_PATH "/users/nfs/Etu3/21104443"

#ifndef _FICHIERS_

//Cette fonction crée une liste contenant le nom des fichiers et répertoire de root_dir
List listdir(char* root_dir);


//Cette fonction vérifie que le fichier existe dans le directory
int file_exists(char* file);

//Cette fonction copie le contenu d'un fichier vers une autre 
void cp(char* to, char* from);
#endif