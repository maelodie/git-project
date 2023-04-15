PROGRAMS=main

all: main

main: hash.o liste.o fichier.o worktree.o main.o
	gcc -Wall hash.o liste.o fichier.o worktree.o main.o -o main

main.o: main.c worktree.h fichier.h liste.h hash.h
	gcc -Wall -c main.c -o main.o

worktree.o: worktree.c worktree.h fichier.h
	gcc -Wall -c worktree.c -o worktree.o

fichier.o: fichier.c fichier.h hash.h
	gcc -Wall -c fichier.c -o fichier.o

liste.o : liste.c liste.h
	gcc -Wall -c liste.c -o liste.o

hash.o: hash.c hash.h
	gcc -Wall -c hash.c -o hash.o

clean: 
	rm -rf *.o ${PROGRAMS}