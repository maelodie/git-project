all: instantane

instantane: hash.o liste.o fichier.o worktree.o instantane.o
	gcc -Wall hash.o liste.o fichier.o worktree.o instantane.o -o instantane

instantane.o: instantane.c worktree.h fichier.h liste.h hash.h
	gcc -Wall -c instantane.c -o instantane.o

worktree.o: worktree.c worktree.h fichier.h
	gcc -Wall -c worktree.c -o worktree.o

fichier.o: fichier.c fichier.h hash.h
	gcc -Wall -c fichier.c -o fichier.o

liste.o : liste.c liste.h
	gcc -Wall -c liste.c -o liste.o

hash.o: hash.c hash.h
	gcc -Wall -c hash.c -o hash.o

clean: 
	rm -rf *.o instantane