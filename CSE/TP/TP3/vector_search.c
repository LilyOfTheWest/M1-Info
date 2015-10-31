#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TAILLE_MAX 12

int main(int argc, char** argv) {
	FILE *fp;
	int *tab;
	int i = 0;
	int n, v, retour;
	char chaine[TAILLE_MAX];
	struct timeval tb, te;

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

	gettimeofday(&tb, NULL);

	for(i=0; i < n; i++) {
		if (tab[i] == v) {
			retour = i;
			break;
		}
	}

	gettimeofday(&te, NULL);

	printf("Temps d'exécution: %lus %luus\n", (unsigned long)te.tv_sec-tb.tv_sec, (unsigned long)te.tv_usec-tb.tv_usec);

	printf("%d\n", retour);

	return 1;
}