# Flags de compilation
CC=gcc
CFLAGS= -Wall -g


# Décommenter le premier pour compiler avec la librairie statique
# Ou le second pour compiler avec la librairie dynamique
LDFLAGS= -L. -lstdes
#LDFLAGS= libstdes.so.1

# Exécutables
EXEC=test moyenne genere_notes
SRC= $(wildcard *.c)

.PHONY: clean mrproper

# Pour compiler avec une librairie statique laisser static
# Remplacer static par dynamic pour compiler avec une librairie dynamique
all: clean static $(EXEC)

test: test.o
	$(CC) -o $@ $^ $(LDFLAGS)

moyenne: moyenne.o
	$(CC) -o $@ $^ $(LDFLAGS)

genere_notes: genere_notes.o
	$(CC) -o $@ $^ $(LDFLAGS)

static: stdes.o
	ar q libstdes.a $^

dynamic: stdes.o
	$(CC) -shared -o libstdes.so.1 $^

%.o: %.c
	$(CC) -fpic -o $@ -c $< $(CFLAGS) 

clean:
	rm -f *.o *.a *.so.*

mrproper: clean
	rm -f $(EXEC)

tests:
	./test test.txt resultat.txt
	./genere_notes 10 notes.txt
	./moyenne notes.txt