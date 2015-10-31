#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MEMOIRE 4096

int main(int argc, char **argv) {
	int i = 0;
	char memoire[TAILLE_MEMOIRE];

	// Initialisation de la mémoire
	mem_init(memoire, TAILLE_MEMOIRE);

	// Test sans débordement de la mémoire
	char *alphabet;
	if ((alphabet = mem_alloc(26 * sizeof(char))) == NULL) {
		printf("Erreur lors de l'allocation de l'aphabet\n");
		return -1;
	}

	printf("\n");

	alphabet[0] = 'a';
	for(i = 1; i < 26; i++) {
		alphabet[i] = alphabet[i-1]+1;
	}

	for(i = 0; i < 26; i++) {
		printf("%c ", alphabet[i]);
	}
	printf("\n");

	mem_free(alphabet);

	// Test avec débordement de la mémoire
	int *compteur;
	if ((compteur = mem_alloc(100 * sizeof(int))) == NULL) {
		printf("Erreur lors de l'allcoation du compteur\n");
		return -1;
	}

	for(i = 0; i <= 100; i++) {
		compteur[i] = i;
	}

	for(i = 0; i <= 100; i++) {
		printf("%i ", compteur[i]);
	}
	printf("\n");

	mem_free(compteur);

	return 0;
}