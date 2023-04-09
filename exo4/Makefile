all : worktree

worktree: worktree.o worktree_main.o
	gcc -Wall worktree.o worktree_main.o -o worktree

worktree_main.o: worktree.h worktree_main.c
	gcc -Wall -c worktree_main.c -o worktree_main.o

worktree.o: worktree.h worktree.c
	gcc -Wall -c worktree.c -o worktree.o

clean:
	rm -rf *.o worktree