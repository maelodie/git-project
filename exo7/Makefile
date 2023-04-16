PROGRAMS=myGit
CC=gcc
CFLAGS=-Wall -Werror

all: myGit

myGit: myGit.o git.o ref.o commit.o worktree.o fichier.o liste.o hash.o
	$(CC) $(CFLAGS) $^ -o $@

myGit.o: myGit.c 
	$(CC) $(CFLAGS) -c $^ -o $@

git.o: git.c
	$(CC) $(CFLAGS) -c $^ -o $@

ref.o: ref.c
	$(CC) $(CFLAGS) -c $^ -o $@

commit.o: commit.c 
	$(CC) $(CFLAGS) -c $^ -o $@

worktree.o: worktree.c 
	$(CC) $(CFLAGS) -c $^ -o $@

fichier.o: fichier.c 
	$(CC) $(CFLAGS) -c $^ -o $@

liste.o: liste.c 
	$(CC) $(CFLAGS) -c $^ -o $@

hash.o: hash.c 
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o PROGRAMS