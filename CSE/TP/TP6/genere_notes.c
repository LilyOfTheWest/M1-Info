#include "stdes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	FICHIER *f1;
	int nb_notes, i;

	if (argc != 3)
		exit(-1);

	nb_notes = atoi(argv[1]);

	srand(time(NULL));

	f1 = ouvrir (argv[2], 'E');
	if (f1 == NULL)
		exit (-1);

	for(i = 0; i < nb_notes; i++) {
		fecriref(f1, "note= %d, coef= %d\n", rand()%20+1, rand()%6+1);
	}

	fermer (f1);

	return 0;
}
