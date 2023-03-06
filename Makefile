all : prog1_3

prog1_3 : prog1_3.o
	gcc -Wall prog1_3.o -o prog1_3

prog1_3.o : prog1_3.c
	gcc -Wall -c prog1_3.c -o prog1_3.o

clean:
	rm -rf *.o