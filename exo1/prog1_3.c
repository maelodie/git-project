#include <stdio.h>
#include <stdlib.h>

int hashFile(char * source, char * dest) {
    int res; 

    //Copie du contenu de source dans un fichier source.txt
    FILE* f1 = fopen("source.txt", "w");
    fprintf(f1, "%s", source);
    fclose(f1);

    //Copie du contenu de dest dans un fichier dest.txt
    FILE* f2 = fopen("dest.txt", "w");
    fprintf(f2, "%s", dest);
    fclose(f2);

    //On affiche le contenu de source.txt, on utilise sha256sum, on l'écrit dans dest.txt
    system("cat source.txt | cat | sha256sum > dest.txt");
    //On supprime source.txt, on affiche l'addresse contenue dans dest.txt
    system("rm source.txt; cat dest.txt");

    //On garde la valeur dans dest.txt pour retourner
    //On copie ce qu'on a trouvé dans dest.txt dans le fichier char* dest
    FILE* f3 = fopen("dest.txt", "r");
    FILE* f4 = fopen(dest, "w");
    fscanf(f3, "%d", &res);
    fprintf(f4,"%d", res);
    fclose(f3);
    fclose(f4);
    system("rm -f dest.txt");    
    return res;   
}

int main() {
    hashFile("partie1.txt", "file.tmp");
    return 0;
}