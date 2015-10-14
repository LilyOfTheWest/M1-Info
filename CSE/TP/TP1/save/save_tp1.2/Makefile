all: tp1

tp1: main.o allocation.o firstfit.o lirecar.o fonction_generale.o nextfit.o
	gcc -o tp1 main.o allocation.o firstfit.o lirecar.o fonction_generale.o nextfit.o -g

allocation.o: allocation.c allocation.h
	gcc -o allocation.o -c allocation.c -W -Wall -g 

fonction_generale.o: fonction_generale.c fonction_generale.h
	gcc -o fonction_generale.o -c fonction_generale.c -W -Wall -g 
    
next_fit.o: next_fit.c next_fit.h fonction_generale.h
	gcc -o next_fit.o -c next_fit.c -W -Wall -g 
    
firstfit.o: firstfit.c firstfit.h allocation.h fonction_generale.h
	gcc -o firstfit.o -c firstfit.c -W -Wall -g

main.o: main.c firstfit.h allocation.h fonction_generale.h
	gcc -o main.o -c main.c -W -Wall -g

clean:
	rm -rfv allocation.o firstfit.o main.o fonction_generale.o next_fit.o

mrproper: clean
	rm -rfv tp1
