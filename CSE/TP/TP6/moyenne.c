#include "stdes.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FICHIER *f1;
	int note, coef, total_coef = 0, somme = 0, nb_notes = 0;
	float moyenne;

	if (argc != 2)
		exit(-1);

	f1 = ouvrir (argv[1], 'L');
	if (f1 == NULL)
		exit (-1);

	while (fliref(f1, "note= %d, coef= %d\n", &note, &coef) > 0) {
		somme += note * coef;
		total_coef += coef;
		nb_notes++;
	}

	moyenne = (float) somme / (float) total_coef;

	printf("La moyenne des %d notes est de %f\n", nb_notes, moyenne);

	fermer (f1);

	return 0;
}
