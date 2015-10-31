#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>

#define M 20

int nb_glaces;

sem_t dring, vente;

void *acheter_glace(void* arg) {
	pthread_t tid = pthread_self();
  	srand ((int) tid);

	sem_wait(&vente);
	usleep(rand() / RAND_MAX * 1000000.);
	nb_glaces--;
	printf("%lu achète une glace, il en reste %d\n", (unsigned long) tid, nb_glaces);
	sem_post(&dring);

	return NULL;
}

void *recharger_glace(void* arg) {
	pthread_t tid = pthread_self();
  	srand ((int) tid);

  	while(1) {
		sem_wait(&dring);
		if (nb_glaces == 0) {
			usleep(rand() / RAND_MAX * 1000000.);
			printf("%lu recharge les glaces\n", (unsigned long) tid);
			nb_glaces += M;
		}
		sem_post(&vente);
	}

	return NULL;
}

int main (int argc, char** argv) {
	int i, nb_acheteur;
	pthread_t *tid_acheteur;
	pthread_t tid_vendeur;

	if (argc != 2 && atoi(argv[1]) <= 0) {
		printf("usage: %s <nb_acheteur>\n\t- nb_acheteur > 0\n", argv[0]);
		return 0;
	}

	nb_acheteur = atoi(argv[1]);

	tid_acheteur = malloc(nb_acheteur * sizeof(pthread_t));

	// On initialise nos sémaphores
	nb_glaces = M;
	sem_init(&vente, 0, 1);
	sem_init(&dring, 0, 0);

	// On créé les threads
	pthread_create(&tid_vendeur, NULL, recharger_glace, NULL);
	for(i=0; i < nb_acheteur; i++) {
		pthread_create(&tid_acheteur[i], NULL, acheter_glace, NULL);
	}

	// On attend la fin des threads
	for(i=0; i < nb_acheteur; i++) {
		pthread_join(tid_acheteur[i], NULL);
	}
	pthread_join(tid_vendeur, NULL);

	free(tid_acheteur);

	return 1;
}