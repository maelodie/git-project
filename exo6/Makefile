PROGRAMS=main

all: main

main: hash.o liste.o fichier.o commit.o main.o
	gcc -Wall hash.o liste.o fichier.o commit.o main.o -o main

main.o: main.c commit.h fichier.h liste.h hash.h
	gcc -Wall -c main.c -o main.o

commit.o: commit.c commit.h fichier.h
	gcc -Wall -c commit.c -o commit.o

fichier.o: fichier.c fichier.h
	gcc -Wall -c fichier.c -o fichier.o

liste.o : liste.c liste.h
	gcc -Wall -c liste.c -o liste.o

hash.o: hash.c hash.h
	gcc -Wall -c hash.c -o hash.o

clean: 
	rm -rf *.o ${PROGRAMS}