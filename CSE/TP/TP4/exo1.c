#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <semaphore.h>

#define M 20

volatile int last_vente;

int nb_glaces;

sem_t glaces, vente, vide;

void *acheter_glace(void* arg) {
	struct timeval t;
	pthread_t tid = pthread_self();
  	srand ((int) tid);

	sem_wait(&glaces);
	sem_wait(&vente);
	usleep(rand() / RAND_MAX * 100000000.);
	nb_glaces--;
	gettimeofday(&t, NULL);
	last_vente = t.tv_sec;
	printf("%lu achète une glace, il en reste %d\n", (unsigned long) tid, nb_glaces);
	if (nb_glaces == 0) {
		sem_post(&vide);
	}
	sem_post(&vente);

	return NULL;
}

void *recharger_glace(void* arg) {
	int i;
	pthread_t tid = pthread_self();
  	srand ((int) tid);

  	while(1) {
		sem_wait(&vide);
		sem_wait(&vente);
		usleep(rand() / RAND_MAX * 10000000.);
		printf("%lu recharge les glaces\n", (unsigned long) tid);
		nb_glaces += M;
		for(i=0; i < M; i++) {
			sem_post(&glaces);
		}
		sem_post(&vente);
	}

	return NULL;
}

int main (int argc, char** argv) {
	int i, nb_acheteur;
	pthread_t *tid_acheteur;
	pthread_t tid_vendeur;
	struct timeval t;

	if (argc != 2 && atoi(argv[1]) <= 0) {
		printf("usage: %s <nb_acheteur>\n\t- nb_acheteur > 0\n", argv[0]);
		return 0;
	}

	nb_acheteur = atoi(argv[1]);

	tid_acheteur = malloc(nb_acheteur * sizeof(pthread_t));

	// On initialise nos sémaphores
	nb_glaces = M;
	sem_init(&glaces, 0, nb_glaces);
	sem_init(&vente, 0, 1);
	sem_init(&vide, 0, 0);

	// On créé les threads
	pthread_create(&tid_vendeur, NULL, recharger_glace, NULL);
	for(i=0; i < nb_acheteur; i++) {
		pthread_create(&tid_acheteur[i], NULL, acheter_glace, NULL);
	}

	// On attend la fin des threads
	for(i=0; i < nb_acheteur; i++) {
		pthread_join(tid_acheteur[i], NULL);
	}

	// Si on a pas eu d'achat dans les 10 secondes on ferme
	while(1) {
		gettimeofday(&t, NULL);
		if (t.tv_sec-last_vente >= 10) {
			free(tid_acheteur);
			exit(1);
		}
	}

	return 1;
}