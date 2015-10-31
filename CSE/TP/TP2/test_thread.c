#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define TAILLE_MEMOIRE 4096

void mem_print(void *zone, size_t taille, int free) {
	if (free) {
		printf("FREE adresse: %lx, taille: %lu\n", (unsigned long)zone, (unsigned long)taille);
	} else {
		printf("BUSY adresse: %lx, taille: %lu\n", (unsigned long)zone, (unsigned long)taille);
	}
}

void *allocations(void *p_data) {
	int i;
	void* test[25];
	int size[25];

	// On fait 25 allocations aléatoires
	for(i=0; i < 25; i++) {
		size[i] = rand() % (216) + 1;
		test[i] = mem_alloc(size[i]);
		if (test[i] == NULL) {
			printf("Thread: allocation NULLE, taille: %i\n", size[i]);
		} else {
			printf("Thread: allocation %lx, taille: %i\n", (unsigned long) test[i], size[i]);
		}
	}

	// Puis on les libères
	for(i=0; i < 25; i++) {
		mem_free(test[i]);
		usleep (rand() / RAND_MAX * 1000000.) ;
	}

	return NULL;
}

int main(int argc, char **argv) {
	pthread_t id_thread;
	char memoire[TAILLE_MEMOIRE];
	int i;
	void* test[35];
	int size[35];

	srand(time(NULL));

	// Initialisation de la mémoire
	printf("\nEtat initial de la mémoire avant des allocations et des libérations en parallèle :\n");
	mem_init(memoire, TAILLE_MEMOIRE);
	mem_show(&mem_print);

	srand(time(NULL));
	
	// On créé un thread parallèle à celui ci
	pthread_create(&id_thread, NULL, allocations, NULL);

	// On fait 35 allocations aléatoires
	for(i=0; i < 35; i++) {
		size[i] = rand() % (216) + 1;
		test[i] = mem_alloc(size[i]);
		if (test[i] == NULL) {
			printf("Principal: allocation NULLE, taille: %i\n", size[i]);
		} else {
			printf("Principal: allocation %lx, taille: %i\n", (unsigned long) test[i], size[i]);
		}
	}

	// Puis on les libères
	for(i=0; i < 35; i++) {
		mem_free(test[i]);
		usleep (rand() / RAND_MAX * 1000000.) ;
	}

	// On attend la fin du thread
	pthread_join(id_thread, NULL);

	// On affiche l'état de la mémoire à la fin des opérations
	// Qui est censé si tout c'est bien passé être une zone entièrement libre
	printf("\nEtat final de la mémoire\n");
	mem_show(&mem_print);

	return 0;
}