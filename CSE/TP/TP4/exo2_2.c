#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>


// SOLUTION AVEC LES SEMAPHORES

// Les structures définies
struct lectred {
	int nb_lecteur;
	sem_t lecture, ecriture;
};

struct linked_list {
	int nb;
	struct linked_list *next;
};

struct linked_list_head {
	struct lectred sync;
	struct linked_list *head;
};

// La liste partagée
struct linked_list_head liste;

void init(struct lectred* l) {
	l->nb_lecteur = 0;
	sem_init(&(l->lecture), 0, 1); // Utilisé en mutex
	sem_init(&(l->ecriture), 0, 1); // Sémaphore car peut être pris en rendu par 2 threads différents
}

void begin_read(struct lectred* l) {
	sem_wait(&(l->lecture));
	l->nb_lecteur++;
	if (l->nb_lecteur == 1) {
		sem_wait(&(l->ecriture));
	}
	sem_post(&(l->lecture));
}

void end_read(struct lectred* l) {
	sem_wait(&(l->lecture));
	l->nb_lecteur--;
	if (l->nb_lecteur == 0) {
		sem_post(&(l->ecriture));
	}
	sem_post(&(l->lecture));
}

void begin_write(struct lectred* l) {
	sem_wait(&(l->ecriture));
}

void end_write(struct lectred* l) {
	sem_post(&(l->ecriture));
}

void list_init(struct linked_list_head *list) {
	list->head = NULL;
	init(&list->sync);
}

int exists(struct linked_list_head *list, int val) {
	struct linked_list *p;
	begin_read(&list->sync);
	sleep(rand()%3 + 1);
	p = list->head;
	while(p != NULL) {
		if (p->nb == val) {
			end_read(&list->sync);
			return 1;
		}
		p = p->next;
	}
	end_read(&list->sync);
	return 0;
}

void add_element(struct linked_list_head *list, struct linked_list *l) {
	struct linked_list **p, **prec;
	begin_write(&list->sync);
	sleep(rand()%3 + 1);
	prec = NULL;
	p = &list->head;
	while((*p) != NULL) {
		prec = p;
		p = &(*p)->next;
	}
	if (prec != NULL) {
		(*prec)->next = l;
	} else {
		list->head = l;
	}
	end_write(&list->sync);
}

struct linked_list* remove_element(struct linked_list_head *list, int val) {
	struct linked_list **p, *ret = NULL;
	begin_write(&list->sync);
	sleep(rand()%3 + 1);
	p = &list->head;
	while((*p) != NULL) {
		if ((*p)->nb == val) {
			ret = *p;
			*p = (*p)->next;
			break;
		}
		p = &(*p)->next;
	}
	end_write(&list->sync);
	return ret;
}

void* lecture(void* arg) {
	pthread_t tid = pthread_self () ;
  	srand ((int) tid) ;

  	// on cherche une valeur random entre 1 et 2
  	int val = rand()%2 + 1;

  	if (exists(&liste, val)) {
  		printf("Lecteur %lu, cherche valeur %d dans la liste : présente\n", (unsigned long) tid, val);
  	} else {
  		printf("Lecteur %lu, cherche valeur %d dans la liste : non présente\n", (unsigned long) tid, val);
  	}

	return NULL;
}

void* ecriture(void* arg) {
	pthread_t tid = pthread_self () ;
  	srand ((int) tid) ;

	// on effectue soit un ajout soit une suppression
  	int val = rand()%2;
  	if (val) {
  		val = rand()%2 + 1;

  		printf("Rédacteur %lu, ajoute la valeur %d dans la liste\n", (unsigned long) tid, val);

  		struct linked_list *l;
  		l = malloc(sizeof(struct linked_list));
  		l->nb = val;
  		l->next = NULL;

  		add_element(&liste, l);
  	} else {
  		val = rand()%2 + 1;

  		struct linked_list *l;
  		if ((l = remove_element(&liste, val)) != NULL) {
  			printf("Rédacteur %lu, supprime la valeur %d dans la liste si elle existe : réussi\n", (unsigned long) tid, val);
  			free(l);
  		} else {
  			printf("Rédacteur %lu, supprime la valeur %d dans la liste si elle existe : raté\n", (unsigned long) tid, val);
  		}
  	}

	return NULL;
}

int main (int argc, char** argv) {
	int i, nb_lecteur, nb_redacteur;
	pthread_t *tid_lecteur;
	pthread_t *tid_redacteur;

	if (argc != 3 && (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0)) {
		printf("usage: %s <nb_lecteur> <nd_redacteur>\n\t- nb_lecteur et nb_redacteur > 0\n", argv[0]);
		return 0;
	}

	// On initialise la liste
	list_init(&liste);

	nb_lecteur = atoi(argv[1]);
	nb_redacteur = atoi(argv[2]);

	tid_lecteur = malloc(nb_lecteur * sizeof(pthread_t));
	tid_redacteur = malloc(nb_redacteur * sizeof(pthread_t));

	// On créé les threads
	for(i=0; i < nb_lecteur; i++) {
		pthread_create(&tid_lecteur[i], NULL, lecture, NULL);
	}

	for(i=0; i < nb_redacteur; i++) {
		pthread_create(&tid_redacteur[i], NULL, ecriture, NULL);
	}


	// On attend la fin des threads
	for(i=0; i < nb_lecteur; i++) {
		pthread_join(tid_lecteur[i], NULL);
	}

	for(i=0; i < nb_redacteur; i++) {
		pthread_join(tid_redacteur[i], NULL);
	}

	free(tid_lecteur);
	free(tid_redacteur);

	return 1;
}