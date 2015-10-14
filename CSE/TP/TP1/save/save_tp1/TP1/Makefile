all: tp1

tp1: main.o allocation.o firstfit.o lirecar.o
	gcc -o tp1 main.o allocation.o firstfit.o lirecar.o -g

allocation.o: allocation.c allocation.h
	gcc -o allocation.o -c allocation.c -W -Wall -g 

firstfit.o: firstfit.c firstfit.h allocation.h
	gcc -o firstfit.o -c firstfit.c -W -Wall -g

main.o: main.c firstfit.h allocation.h
	gcc -o main.o -c main.c -W -Wall -g

clean:
	rm -rfv allocation.o firstfit.o main.o

mrproper: clean
	rm -rfv tp1
