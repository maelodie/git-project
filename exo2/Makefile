PROGRAMS= liste_main 

all : liste_main

liste_main : liste_main.o liste.o
	gcc -Wall liste_main.o liste.o -o liste_main

liste_main.o: liste_main.c liste.h
	gcc -Wall -c liste_main.c -o liste_main.o

liste.o: liste.c liste.h
	gcc -Wall -c liste.c -o liste.o

clean:
	rm -rf *.o $(PROGRAMS)
