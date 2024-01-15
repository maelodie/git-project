#ifndef _HASH_
#define _HASH_

//Cette fonction copie le contenu de source vers dest
int hashFile(char* source, char* dest);

//Cette fonction renvoie une chaine de caractères contenant le hash du fichier en paramètres
char* sha256file(char* file);

#endif