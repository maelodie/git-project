PROGRAMS=prog1_3 prog1_4

all : $(PROGRAMS)

prog1_3 : prog1_3.o
	gcc -Wall prog1_3.o -o prog1_3

prog1_3.o : prog1_3.c
	gcc -Wall -c prog1_3.c -o prog1_3.o

prog1_4: prog1_4.o
	gcc -Wall prog1_4.o -o prog1_4

prog1_4.o: prog1_4.c
	gcc -Wall -c prog1_4.c -o prog1_4.o

clean:
	rm -rf *.o $(PROGRAMS)