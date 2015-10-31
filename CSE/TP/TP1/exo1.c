#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int rang; /* Initialisé par creer_processus */

void creer_processus(int n);
void tirage_aleatoire();
void attendre_fin_processus(int n);

int main(int argc, char* argv[]) {
	int n;

	/* On vérifie que l'utilisateur ait entré le bon nombre d'arguments
	 * et la bonne valeur
	 */
	if (argc != 2 || atoi(argv[1]) <= 1) {
		printf("Utilisation: exo1 <n>\n");
		printf("\tn : entier > 1\n");
		return -1;
	}

	n = atoi(argv[1]);

	creer_processus(n-1);

	tirage_aleatoire();

	if (rang == 0) {
		attendre_fin_processus(n-1);
	}

	return 0;
}

void creer_processus(int n) {
	int i = 0;

	/* On met le rang du père à 0 */
	rang = 0;

	/* Puis on créé tous les fils nécessaires */
	for(i = 0; i < n; i++) {
		pid_t pid = fork();
		switch(pid) {
			case 0:
				rang = i+1;
				return;
			case -1:
				perror("fork");
				exit(-1);
		}
	}
}

void tirage_aleatoire() {
	int val;

	/* On utilise srand avec une graine différente à chaque tirage aléatoire */
	srand(getpid());

	val = rand();

	/* Puis on affiche la valeur de ce processus */
	printf("processus pid %d node %d val = %d\n", getpid(), rang, val);
}

void attendre_fin_processus(int n) {
	int status, i = 0;

	/* On attend la fin de tous les fils */
	for (i = 0; i < n; i++) {
		wait(&status);
	}
}