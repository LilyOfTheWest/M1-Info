all: tp1

tp1: main.o allocation.o firstfit.o lirecar.o fonction_generale.o nextfit.o bestfit.o
	gcc -o tp1 main.o allocation.o firstfit.o lirecar.o fonction_generale.o nextfit.o bestfit.o -g

allocation.o: allocation.c allocation.h
	gcc -o allocation.o -c allocation.c -W -Wall -g 

fonction_generale.o: fonction_generale.c fonction_generale.h
	gcc -o fonction_generale.o -c fonction_generale.c -W -Wall -g 
    
nextfit.o: nextfit.c nextfit.h allocation.h fonction_generale.h
	gcc -o nextfit.o -c nextfit.c -W -Wall -g 

bestfit.o: bestfit.c bestfit.h allocation.h fonction_generale.h
	gcc -o bestfit.o -c bestfit.c -W -Wall -g 
    
firstfit.o: firstfit.c firstfit.h allocation.h fonction_generale.h
	gcc -o firstfit.o -c firstfit.c -W -Wall -g

main.o: main.c firstfit.h nextfit.h bestfit.h allocation.h fonction_generale.h
	gcc -o main.o -c main.c -W -Wall -g

clean:
	rm -rfv allocation.o firstfit.o main.o fonction_generale.o nextfit.o bestfit.o

mrproper: clean
	rm -rfv tp1
