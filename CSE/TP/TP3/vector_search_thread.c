#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define TAILLE_MAX 12

volatile int retour;

struct recherche {
	int *tab;
	int inf;
	int sup;
	int v;
};

void* find(void* arg) {
	struct recherche *r = (struct recherche*) arg;
	int i;

	for(i=r->inf; i < r->sup; i++) {
		if (retour != -1) {
			return NULL;
		}
		if (r->tab[i] == r->v) {
			retour = i;
			return NULL;
		}
	}

	return NULL;
}

int main(int argc, char** argv) {
	FILE *fp;
	int *tab;
	int i = 0;
	int n, v;
	char chaine[TAILLE_MAX];
	struct timeval tb, te;
	pthread_t id;
	struct recherche b1;

	if (argc != 3) {
		printf("usage: %s <fichier> <valeur>\n", argv[0]);
		return -1;
	}

	v = atoi(argv[2]);

	fp = fopen(argv[1],"r");

	if (fp == NULL) {
		printf("Erreur à l'ouverture du fichier\n");
		return -1;
	}

	if (fgets(chaine, TAILLE_MAX, fp) != NULL) {
		n = atoi(chaine);
		tab = malloc(n*sizeof(int));
	}

	while (fgets(chaine, TAILLE_MAX, fp) != NULL) {
        tab[i++] = atoi(chaine);
    }

	fclose(fp);

	retour = -1;

	b1.tab = tab;
	b1.inf = 0;
	b1.sup = n/2;
	b1.v = v;

	gettimeofday(&tb, NULL);

	pthread_create(&id, NULL, find, (void*)&b1);

	for(i=n-1; i >= n/2; i--) {
		if (retour != -1) {
			break;
		}
		if (tab[i] == v) {
			retour = i;
			break;
		}
	}

	pthread_join(id, NULL);

	gettimeofday(&te, NULL);

	printf("Temps d'exécution: %lus %luus\n", (unsigned long)te.tv_sec-tb.tv_sec, (unsigned long)te.tv_usec-tb.tv_usec);

	printf("%d\n", retour);

	return 1;
}