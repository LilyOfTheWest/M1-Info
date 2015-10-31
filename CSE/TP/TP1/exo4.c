#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int rang; /* Initialisé par creer_processus */

/* Structure d'envoi de message */
typedef struct Processus{
	int rang;
	int pid;
	int val;
}Processus;

void *creer_memoire_partagee(size_t size, int *shmid);
void initialiser_memoire_partagee(int n, void *ptr);
void creer_processus(int n);
int tirage_aleatoire();
void communication(int n, int val, void *ptr);
void attendre_fin_processus(int n);
void detruire_memoire_partagee(void *ptr, int shmid);
void handle_error(char *function_name, int return_value);

int main(int argc, char* argv[]) {
	int n, val, shmid;
	void *ptr;

	/* On vérifie que l'utilisateur ait entré le bon nombre d'arguments
	 * et la bonne valeur
	 */
	if (argc != 2 || atoi(argv[1]) <= 1) {
		printf("Utilisation: exo4 <n>\n");
		printf("\tn : entier > 1\n");
		return -1;
	}

	n = atoi(argv[1]);

	ptr = creer_memoire_partagee(n*sizeof(Processus), &shmid);

	initialiser_memoire_partagee(n, ptr);

	creer_processus(n-1);

	val = tirage_aleatoire();

	communication(n, val, ptr);

	if (rang == 0) {
		attendre_fin_processus(n-1);

		detruire_memoire_partagee(ptr, shmid);
	}

	return 0;
}

/* Fonction prise sur le sujet du TP */
void *creer_memoire_partagee(size_t size, int *shmid) {
	void *ptr;

	*shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
	handle_error("shmget", *shmid);
	ptr = shmat(*shmid, NULL, 0);
	handle_error("shmat", *(int*) ptr);

	return ptr;
}

void initialiser_memoire_partagee(int n, void *ptr) {
	int i;
	Processus *p = (Processus*) ptr;

	/* On initialise les informations dans le segment à -1 */
	for(i = 0; i < n; i++) {
		p[i].val = -1;
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

int tirage_aleatoire() {
	int val;

	/* On utilise srand avec une graine différente à chaque tirage aléatoire */
	srand(getpid());

	val = rand();

	/* Puis on affiche la valeur de ce processus */
	printf("processus pid %d node %d val = %d\n", getpid(), rang, val);

	return val;
}

void communication(int n, int val, void *ptr) {
	Processus *p = (Processus*) ptr;

	if (rang == 0) {
		p[0].rang = 0;
		p[0].pid = getpid();
		p[0].val = val;

		/* On attend que le dernier processus ait entré sa valeur */
		while(p[n-1].val == -1) { 
			sleep(0.1);
		}

		/* Puis on affiche le résultat */
		printf("the winner is %i pid %i node %i\n", p[n-1].val, p[n-1].pid, p[n-1].rang);
	} else {
		/* On attend que le processus précédent ait entré sa valeur */
		while(p[rang-1].val == -1) {
			sleep(0.1);
		}

		/* Puis on compare les valeurs et on récupère la plus grande des deux */
		if (p[rang-1].val > val) {
			p[rang] = p[rang-1];
		} else {
			p[rang].rang = rang;
			p[rang].pid = getpid();
			p[rang].val = val;
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

/* Fonction prise sur le sujet du TP */
void detruire_memoire_partagee(void *ptr, int shmid) {
	int cr;

	cr = shmdt(ptr);
	handle_error("shmdt", cr);
	cr = shmctl(shmid, IPC_RMID, NULL);
	handle_error("shmctl", cr);
}

/* Fonction prise sur le sujet du TP */
void handle_error(char *function_name, int return_value) {
	char message[128] = "Error in function ";
	if (return_value == -1) {
		perror(strcat(message, function_name));
		exit(-1);
	}
}