#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MEMOIRE 4096

void mem_print(void *zone, size_t taille, int free) {
	if (free) {
		printf("FREE adresse: %lx, taille: %lu\n", (unsigned long)zone, (unsigned long)taille);
	} else {
		printf("BUSY adresse: %lx, taille: %lu\n", (unsigned long)zone, (unsigned long)taille);
	}
}

int main(int argc, char **argv) {
	char memoire[TAILLE_MEMOIRE];
	void* test[6];

	mem_init(memoire, TAILLE_MEMOIRE);
	
	if (argc == 2) {
		switch(atoi(argv[1])) {
			case 1:
				printf("\nUtilisation de First Fit :\n");
				break;
			case 2:
				printf("\nUtilisation de Best Fit :\n");
				mem_fit(&mem_fit_best);
				break;
			case 3:
				printf("\nUtilisation de Worst Fit :\n");
				mem_fit(&mem_fit_worst);
				break;
			default:
				printf("Erreur d'utilisation ! \n");
				exit(-1);
		}
	} else {
		printf("Erreur d'utilisation !\n");
		exit(-1);
	}

	printf("\nInitialisation\n");

	printf("Alloc 0 de 500\n");
	test[0] = mem_alloc(500);

	printf("Alloc 1 de 1000\n");
	test[1] = mem_alloc(1000);

	printf("Alloc 2 de 1000\n");
	test[2] = mem_alloc(1000);

	printf("Alloc 4 de 300\n");
	test[4] = mem_alloc(300);

	printf("Alloc 5 de 850\n");
	test[5] = mem_alloc(850);

	printf("Free de test 0\n");
	mem_free(test[0]);

	printf("Free de test 2\n");
	mem_free(test[2]);

	printf("Free de test 4\n");
	mem_free(test[4]);

	printf("\nMémoire avant allocation montrant la stratégie utilisée : \n");
	mem_show(&mem_print);

	printf("\nAlloc 3 de 256 : \n");
	test[3] = mem_alloc(256);
	mem_show(&mem_print);

	printf("\nFree de test 1\n");
	mem_free(test[1]);

	printf("Free de test 3\n");
	mem_free(test[3]);

	printf("Free de test 4\n");
	mem_free(test[4]);

	return 0;
}