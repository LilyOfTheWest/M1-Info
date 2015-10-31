#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int rang; /* Initialisé par creer_processus */

/* Structure d'envoi de message */
typedef struct Message{
	int rang;
	int pid;
	int val;
}Message;

void creer_tubes(int n, int** tubes);
void creer_processus(int n);
void selection_tubes(int n, int **tubes, int *tlect, int *tecr);
int tirage_aleatoire();
void communication(int n, int val, int *tlect, int *tecr);
void attendre_fin_processus(int n);

int main(int argc, char* argv[]) {
	int n, tlect, tecr, val, i;
	int **tubes;

	/* On vérifie que l'utilisateur ait entré le bon nombre d'arguments
	 * et la bonne valeur
	 */
	if (argc != 2 || atoi(argv[1]) <= 1) {
		printf("Utilisation: exo3 <n>\n");
		printf("\tn : entier > 1\n");
		return -1;
	}

	n = atoi(argv[1]);

	/* On alloue dynamiquement notre tableau de tubes */
	tubes = malloc(n * sizeof(int*));
	
	for(i = 0; i < n; i++) {
		tubes[i] = malloc(2 * sizeof(int));
	}

	creer_tubes(n, tubes);

	creer_processus(n-1);

	selection_tubes(n, tubes, &tlect, &tecr);

	val = tirage_aleatoire();

	communication(n, val, &tlect, &tecr);

	if (rang == 0) {
		attendre_fin_processus(n-1);

		free(tubes);
	}

	return 0;
}

void creer_tubes(int n, int** tubes) {
	int i;

	/* On créé n tubes qui serviront à communiquer entre les processus */
	for(i = 0; i < n; i++) {
		pipe(tubes[i]);
	}
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

/* On récupère les file descriptor des tubes */
void selection_tubes(int n, int** tubes, int *tlect, int *tecr) {
	int i, ecr, lect;

	/* On récupère les bons tubes qui serviront à transmettre de l'information */
	if (rang == 0) {
		*tlect = tubes[n-1][0];
		*tecr = tubes[0][1];

		ecr = 0;
		lect = n-1;
	} else if (rang == n-1) {
		*tlect = tubes[n-2][0];
		*tecr = tubes[n-1][1];

		ecr = n-1;
		lect = n-2;
	} else {
		*tlect = tubes[rang-1][0];
		*tecr = tubes[rang][1];

		ecr = rang;
		lect = rang-1;
	}

	/* Puis on ferme tous les liens inutiles pour le processus en cours */
	for(i = 0; i < n; i++) {
		if (i == ecr) {
			close(tubes[i][0]);
		} else if (i == lect) {
			close(tubes[i][1]);
		} else {
			close(tubes[i][0]);
			close(tubes[i][1]);
		}
	}
}

int tirage_aleatoire() {
	int val;

	/* On utilise srand avec une graine différente à chaque tirage aléatoire */
	srand(getpid());

	val = rand();

	/* Puis on affiche la valeur de ce processus */
	printf("processus pid %d node %d val = %d\n", getpid(), rang, val);

	return val;
}

void communication(int n, int val, int *tlect, int *tecr) {
	Message envoi, retour;

	if (rang == 0) {
		envoi.rang = rang;
		envoi.pid = getpid();
		envoi.val = val;

		/* Si on est le père, on va d'abords écrire sa valeur, puis attendre une réponse */
		if (write(*tecr, &envoi, sizeof(envoi)) == -1) {
			perror("Erreur lors de l'écriture dans un tube !");
			exit(-1);
		}

		if (read(*tlect, &retour, sizeof(retour)) == -1) {
			perror("Erreur lors de la lecture dans un tube !");
			exit(-1);
		}

		/* On récupère la dernière valeur qui correspond au gagnant et on l'affiche */
		printf("Node %i the winner is %i pid %i node %i\n", rang, retour.val, retour.pid, retour.rang);

		/* On renvoi ensuite le gagnant aux autres processus */
		if (write(*tecr, &retour, sizeof(retour)) == -1) {
			perror("Erreur lors de l'écriture dans un tube !");
			exit(-1);
		}
	} else {
		/* Sinon on va lire la valeur reçu, la comparer puis écrire la plus grande */
		if (read(*tlect, &retour, sizeof(retour)) == -1) {
			perror("Erreur lors de la lecture dans un tube !");
			exit(-1);
		}

		if (val > retour.val) {
			envoi.rang = rang;
			envoi.pid = getpid();
			envoi.val = val;
		} else {
			envoi = retour;
		}

		if (write(*tecr, &envoi, sizeof(envoi)) == -1) {
			perror("Erreur lors de l'écriture dans un tube !");
			exit(-1);
		}

		/* On récupère ensuite le gagnant et on l'affiche */
		if (read(*tlect, &retour, sizeof(retour)) == -1) {
			perror("Erreur lors de la lecture dans un tube !");
			exit(-1);
		}

		printf("Node %i the winner is %i pid %i node %i\n", rang, retour.val, retour.pid, retour.rang);

		/* Sauf si on est le dernier processus, on envoie le gagnant au suivant */
		if (rang != n-1) {
			if (write(*tecr, &retour, sizeof(retour)) == -1) {
				perror("Erreur lors de l'écriture dans un tube !");
				exit(-1);
			}
		}
	}
}

void attendre_fin_processus(int n) {
	int status, i = 0;

	/* On attend la fin de tous les fils */
	for (i = 0; i < n; i++) {
		wait(&status);
	}
}