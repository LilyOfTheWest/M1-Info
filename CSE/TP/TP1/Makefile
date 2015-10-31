all: exo1 exo2 exo3 exo4

exo1: exo1.o
		gcc -o exo1 exo1.o

exo1.o: exo1.c
		gcc -o exo1.o -c exo1.c -W -Wall -ansi -pedantic

exo2: exo2.o
		gcc -o exo2 exo2.o

exo2.o: exo2.c
		gcc -o exo2.o -c exo2.c -W -Wall -ansi -pedantic

exo3: exo3.o
		gcc -o exo3 exo3.o

exo3.o: exo3.c
		gcc -o exo3.o -c exo3.c -W -Wall -ansi -pedantic

exo4: exo4.o
		gcc -o exo4 exo4.o

exo4.o: exo4.c
		gcc -o exo4.o -c exo4.c -W -Wall -ansi -pedantic -D_XOPEN_SOURCE

clean:
		rm -f *.o

mrproper: clean
		rm exo1 exo2 exo3 exo4