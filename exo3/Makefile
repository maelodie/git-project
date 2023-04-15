PROGRAMS=fichier
all : fichier

fichier : fichiers_main.o fichiers.o liste.o hash.o
	gcc -Wall fichiers_main.o fichiers.o liste.o hash.o -o fichier

fichiers_main.o : fichiers_main.c fichier.h 
	gcc -Wall -c fichiers_main.c -o fichiers_main.o 

fichiers.o : fichiers.c fichier.h hash.h liste.h
	gcc -Wall -c fichiers.c -o fichiers.o

liste.o: liste.c liste.h 
	gcc -Wall -c liste.c -o liste.o

hash.o: hash.c hash.h
	gcc -Wall -c hash.c -o hash.o

clean : 
	rm -rf *.o