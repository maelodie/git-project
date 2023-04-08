PROGRAMS=fichier
all : fichier

fichier : fichiers_main.o fichiers.o liste.o
	gcc -Wall fichiers_main.o fichiers.o liste.o -o fichier

fichiers_main.o : fichiers_main.c fichier.h liste.h
	gcc -Wall -c fichiers_main.c -o fichiers_main.o 

fichiers.o : fichiers.c fichier.h liste.h
	gcc -Wall -c fichiers.c -o fichiers.o

clean : 
	rm -rf *.o