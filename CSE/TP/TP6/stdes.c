#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "stdes.h"

// Taille du Buffer
#define TAILLE_BUFF 100
// Nombre maximum de fichiers ouvert à la fois
#define FICHIERS_OUVERT_MAX 15

// Structure de fichier
struct _ES_FICHIER {
	int fd;
	char buff[TAILLE_BUFF];
	int nb_lu;
	int pos;
	char mode;
};

// Structure listant tous les fichiers ouverts
struct _FICHIERS_OUVERT {
	FICHIER* tab[FICHIERS_OUVERT_MAX];
	unsigned int nb;
};

// Variable globale de nos fichiers ouverts
struct _FICHIERS_OUVERT fouvert = {.tab = {NULL}, .nb = 0};

FICHIER *ouvrir(char *nom, char mode) {
	// Si le mode d'ouverture est inconnu on retourne NULL
	if (mode != 'L' && mode != 'E') {
		return NULL;
	}

	// Si le nombre de fichiers ouvert est déjà au maximum on retourne NULL
	if (fouvert.nb == FICHIERS_OUVERT_MAX) {
		return NULL;
	}

	// On alloue dynamiquement notre fichier
	FICHIER *f = (FICHIER *) calloc(sizeof(struct _ES_FICHIER),1);
	
	if (mode == 'L') {
		// On ouvre le fichier en lecture et on récupère le descripteur de fichier
		// Sinon on libère le fichier et on renvoi NULL
		if ((f->fd = open(nom, O_RDONLY)) == -1) {
			free(f);
			return NULL;
		}
		f->mode = 'L';
	} else {
		// On ouvre le fichier en écriture et on récupère le descripteur de fichier
		// Le fichier est créé si il n'existe pas et est vidé de son contenu si il existe
		// Sinon on libère le fichier et on renvoi NULL
		if ((f->fd = open(nom, O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1) {
			free(f);
			return NULL;
		}
		f->mode = 'E';
	}
	
	// On parcours notre liste de fichiers ouvert et on l'ajoute à la première place libre
	int i;
	for(i = 0; i < FICHIERS_OUVERT_MAX; i++) {
		if (fouvert.tab[i] == NULL) {
			fouvert.tab[i] = f;
			fouvert.nb++;
			break;
		}
	}

	// On met notre position du buffer à 0
	f->pos = 0;

	return f;
}

int fermer(FICHIER *f) {
	// Si le pointeur est NULL on renvoie -1
	if (f == NULL) {
		return -1;
	}

	// Si le fichier est en écriture et que le buffer n'a pas été vidéns le
	// Alors on écrit ce qu'il reste dans le fichier
	if (f->mode == 'E' && f->pos != 0) {
		write(f->fd, f->buff, f->pos);
		f->pos = 0;
	}
	
	// Et on l'enlève de la liste des fichiers ouverts
	int i;
	for(i = 0; i < FICHIERS_OUVERT_MAX; i++) {
		if (fouvert.tab[i] == f) {
			fouvert.tab[i] = NULL;
			fouvert.nb--;
			break;
		}
	}

	// Puis on libère f et on renvoit le résultat
	int retour = close(f->fd);
	free(f);

	return retour;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f) {
	// On retourne -1 si FICHIER est null
	if (f == NULL) {
		return -1;
	}

	// On retourne 0 si le nombre d'élément à lire est de 0
	if (nbelem == 0) {
		return 0;
	}

	int nb_a_lire = taille*nbelem;
	int retour = nb_a_lire;

	// Tant qu'on a quelque chose à lire
	while(nb_a_lire > 0) {

		// Si ce qu'on doit lire est inférieur ou égal à ce qu'il nous reste dans le buffer
		if (nb_a_lire <= TAILLE_BUFF-f->pos) {

			// Si notre position dans le buffer est à 0 alors on va appeler
			// l'appel système read avec TAILLE_BUFF caractère à lire
			// On stocke le nombre de caractères lu, si cette valeur est inférieure à TAILLE_BUFF
			// Alors il n'y a plus rien a lire dans le fichier
			if (f->pos == 0) {
				if ((f->nb_lu = read(f->fd, f->buff, TAILLE_BUFF)) == -1) {
					return -1;
				}
			}

			//On copie dans notre buffer nb_a_lire caractères
			strncpy((char*)p, f->buff+f->pos, nb_a_lire);

			// On incrémente notre position
			f->pos += nb_a_lire;

			// Et si celle ci est égale à TAILLE_BUFF alors on a fini de lire le buffer
			if (f->pos == TAILLE_BUFF) {
				f->pos = 0;
			}

			// On retourne 0 si il n'y a plus rien à lire
			// Le nombre de caractères lu sinon
			return f->pos-1 == f->nb_lu ? 0 : retour;
		} else {
			// De même si on à la position à 0 on refait appel à read
			if (f->pos == 0) {
				if ((f->nb_lu = read(f->fd, f->buff, TAILLE_BUFF)) == -1) {
					return -1;
				}
			}

			// On copie tout ce qu'il reste dans notre buffer dans p
			strncpy((char*)p, f->buff+f->pos, TAILLE_BUFF-f->pos);

			// On décrémente le nombre de caractère restant à lire
			nb_a_lire -= TAILLE_BUFF-f->pos;

			// On remet notre position à 0
			f->pos = 0;
		}
	}

	return 0;
}

int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f) {
	// Si le fichier est NULL on renvoie -1
	if (f == NULL) {
		return -1;
	}

	// On retourne -1 si le nombre d'élément à lire est à 0
	if (nbelem == 0) {
		return -1;
	}

	int nb_a_ecrire = taille*nbelem;
	int retour = nb_a_ecrire;

	// Tant qu'on a quelque chose à écrire
	while(nb_a_ecrire > 0) {

		// Si ce qu'il reste à écrire est inférieur ou égal à la place qui reste dans le buffer
		if (nb_a_ecrire <= TAILLE_BUFF-f->pos) {

			// On copie dans le buffer nb_a_ecrire caractères de p
			strncpy(f->buff+f->pos, (char*)p, nb_a_ecrire);

			// On incrémente notre position
			f->pos += nb_a_ecrire;

			// Si celle ci est égal à TAILLE_BUFF alors on a remplit notre buffer
			// On va donc remettre notre position à 0 et faire un write de notre buffer
			// dans le fichier
			if (f->pos == TAILLE_BUFF) {
				f->pos = 0;
				if (write(f->fd, f->buff, TAILLE_BUFF) == -1) {
					return -1;
				}
			}

			// On retourne le nombre de caractères écrit
			return retour;
		} else {
			// On copie p dans notre buffer de la place qu'il reste
			strncpy(f->buff+f->pos, (char*)p, TAILLE_BUFF-f->pos);

			// On décrémente notre nombre de caractères à écrire
			nb_a_ecrire -= TAILLE_BUFF-f->pos;

			// On remet notre position de buffer à 0
			f->pos = 0;
		}
	}

	return 0;
}

int fliref(FICHIER *f, const char *format, ...) {
	// Si le fichier est NULL alors on revoie -1
	if (f == NULL) {
		return -1;
	}

	va_list ap;
	va_start(ap, format);

	int i = 0;
	int retour = 0;

	// Tant qu'on ne lit pas le caractère de fin de chaîne
	while(format[i] != '\0') {

		// Si la caractère lu est un % alors on regarde le caractère d'après
		if (format[i] == '%') {
			i++;
			switch(format[i]) {
				case 'c':
				{
					// Si c'est c alors on lit un seul caractères
					char *c = va_arg(ap, char*);
					if (lire(c, 1, 1, f) == -1) {
						return -1;
					}

					// On incrémente le nombre d'élément lu
					retour++;
				}
					break;
				case 's':
				{
					// Si c'est s alors on lit tous les caractères jusqu'a
					// un espace ou un retour à la ligne
					char *s = va_arg(ap, char*);
					char c;
					int test;

					// On lit le premier caractère
					if ((test = lire(&c, 1, 1, f)) == -1) {
						return -1;
					}

					// On continue tant qu'on ne lit pas un espace ou un retour à la ligne
					// Et qu'on a pas atteint la fin du fichier
					while(c != ' ' && c != '\n' && test != 0) {
						strcat(s, &c);
						if ((test = lire(&c, 1, 1, f)) == -1) {
							return -1;
						}
					}

					// On décrémente la position car on est sur un caractère n'appartenant pas à la chaine
					// en sortant de la boucle
					f->pos--;
					if (f->pos < 0) {
						f->pos = TAILLE_BUFF-1;
					}

					// On incrémente le nombre d'élément lu
					retour++;
				}
					break;
				case 'd':
				{
					// Si c'est d alors on lit les chiffres jusqu'a un espace ou un retour à la ligne
					int *d = va_arg(ap, int*);
					int signe = 0, test = 1;
					char c;

					// On lit le premier caractère
					if (lire(&c, 1, 1, f) == -1) {
						return -1;
					} 


					// Si c'est un - alors on garde cette information et on lit le caractère suivant
					if (c == '-') {
						signe = 1;
						if (lire(&c, 1, 1, f) == -1) {
							return -1;
						}
					}

					// Tant qu'on lit un chiffre et qu'on est pas à la fin du fichier
					// On multiplie notre entier par 10 puis on ajoute le chiffre lu
					*d = 0;
					while (c >= '0' && c <= '9' && test != 0) {
						*d *= 10;
						*d += atoi(&c);

						if ((test = lire(&c, 1, 1, f)) == -1) {
							return -1;
						}
					}

					// On décrémente la position car on est plus sur un chiffre
					f->pos--;
					if (f->pos < 0) {
						f->pos = TAILLE_BUFF-1;
					}

					// Si le signe est à 1 alors le nombre est négatif donc on le 
					// multiplie par -1
					if (signe == 1) {
						*d *= -1;
					}

					// On incrémente le nombre d'élément lu
					retour++;
				}
					break;
				default:
					break;
			}
		} else if (format[i] == ' ') {
			// Si on lit un espace dans le format alors on continue de lire
			// le fichier tant qu'on a des espaces
			char c;
			int test;

			do {
				if ((test = lire(&c, 1, 1, f)) == -1) {
					return -1;
				}
			} while(c == ' ' || test == 0);

			// On décrémente la position pour ne pas perdre le dernier élément lu
			f->pos--;
			if (f->pos < 0) {
				f->pos = TAILLE_BUFF-1;
			}
		} else {
			// Sinon lorsqu'on lit un caractère dans la chaine de format
			// On lit le prochain caractère du fichier
			// Si ceux ci sont les mêmes on continue
			// Sinon on arrete car le format n'est pas respecté
			char c;
			int test;

			if ((test = lire(&c, 1, 1, f)) == -1) {
				return -1;
			}

			if (test == 0 || c != format[i]) {
				va_end(ap);
				return retour;
			}
		}
		i++;
	}

	va_end(ap);

	return retour;
}

int fecriref(FICHIER *f, const char *format, ...) {
	// Si le fichier est NULL on renvoie -1
	if (f == NULL) {
		return -1;
	}

	va_list ap;
	va_start(ap, format);

	int i = 0;
	int retour = 0;

	// Tant qu'on ne lit pas le caractère de fin de chaine
	while(format[i] != '\0') {
		// Si le caractère lu est un % on lit le caractère suivant
		if (format[i] == '%') {
			i++;
			switch(format[i]) {
				case 'c':
				{
					// Si c'est c on récupère le char en paramètre et on l'écrit dans le fichier
					char c = va_arg(ap, int);
					if (ecrire(&c, 1, 1, f) == -1) {
						return -1;
					}

					// On incrémente la nombre de caractères écrit
					retour++;
				}
					break;
				case 's':
				{
					// Si c'est s on récupère la chaine en paramètre et on l'écrit dans le fichier
					char* s = va_arg(ap, char*);
					if (ecrire(s, 1, strlen(s), f) == -1) {
						return -1;
					}

					// On incrémente le nombre de caractères écrit
					retour += strlen(s);
				}
					break;
				case 'd':
				{
					// Si c'est d on récupère l'entier et on le convertit en chaine puis on
					// l'écrit dans le fichier
					char *s = conversion(va_arg(ap, int));
					if (ecrire(s, 1, strlen(s), f) == -1) {
						return -1;
					}

					// On incrémente le nombre de caractère écrit
					retour += strlen(s);
				}
					break;
				default:
					break;
			}
		} else {
			// Sinon on écrit le caractère lu dans la chaine du format
			if (ecrire(&format[i], 1, 1, f) == -1) {
				return -1;
			}

			// On incrémente le nombre de caractère écrit
			retour++;
		}
		i++;
	}

	va_end(ap);

	// On retourne le nombre de caractère écrit
	return retour;
}

// Fonction qui prend un entier en paramètre et qui renvoit cet entier sous
// forme de chaine de caractère
char *conversion(int n) {
	// Si le caractère est 0 alors on renvoit la chaine 0\0
	if (n == 0) {
		return "0\0";
	}

	char *s;
	int i = 0, taille = 0, tmp = n;

	// On calcule la taille de la chaine
	while(tmp != 0) {
		tmp = tmp/10;
		taille++;
	}

	// On ajoute 1 pour le \0 et 1 de plus pour un nombre négatif
	taille++;
	if (n < 0) {
		taille++;
	}

	// On alloue notre chaine de la taille désiré
	if ((s = malloc(taille*sizeof(char))) == NULL) {
		return NULL;
	}

	// On met le \0 à la fin de la chaine
	s[taille-1] = '\0';
	i = taille-2;

	// Si le nombre est négatif on met le - en début de chaine 
	// et on multiplie notre nombre par -1 pour le remettre positif
	// pour la suite du traitement
	if (n < 0) {
		s[0] = '-';
		n *= -1;
	}

	// On fait le modulo du nombre qu'on ajoute en fin de chaine
	// Puis on divise notre nombre par 10
	while(n != 0) {
		s[i] = '0' + (n%10);
		n = n/10;
		i--;
	}

	// Enfin on retourne la chaine générée
	return s;
}