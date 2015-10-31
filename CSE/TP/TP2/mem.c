#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Alignement */
#define ALIGNEMENT (sizeof(void*))
#define TAILLE_ALIGN(x) (((x) + ALIGNEMENT-1)&~(ALIGNEMENT-1))

/* Valeur servant au débordement */
#define DEBORDEMENT 0xDEADBEEF

/* Structure de données pour les descripteurs des zones libres */
struct fb {
	size_t size;
	struct fb *next;
};

/* Structure de données pour les blocs occupés */
struct bb {
	size_t size;
};

/* VARIABLES GLOBALES */
char* mem_begin = NULL; 				/* Pointeur de début de mémoire */
size_t mem_size = 0;					/* Taille de la zone mémoire */
struct fb mem_ll; 						/* Pointeur sur la première zone libre */
mem_fit_function_t *strategy = NULL; 	/* Pointeur vers la fonction de stratégie choisie */
pthread_mutex_t lock;					/* Mutex pour empêcher une allocation et une libération simultané */

void mem_init(char* mem, size_t taille) {
	/* On initialise notre stratégie à mem_fit_first */
	mem_fit(&mem_fit_first);

	/* On fait pointer notre début de zone mémoire sur le tableau envoyé */
	mem_begin = mem;
	mem_size = taille;

	/* On initialise notre premier block de zone libre qui prend toute la zone */
	struct fb *init = (struct fb*)mem_begin;
	init->size = taille;
	init->next = NULL;

	/* On fait pointer mem_ll sur cette zone */
	mem_ll.next = (struct fb*)mem_begin;
}

void* mem_alloc(size_t taille) {
	/* On renvoie NULL si la taille demandée est <= à 0 */
	if (taille <= 0) {
		return NULL;
	}

	/*
	 * On récupère la taille à allouer qui correspond à :
	 * la taille d'une structure de bloc alloué +
	 * la taille alignée de : la taille demandé + la taille d'une zone de débordement
	 */
	size_t taille_align = sizeof(struct bb) + TAILLE_ALIGN(taille + sizeof(long));

	/* On vérrouille cette partie pour empêcher une libération simultanée */
	pthread_mutex_lock(&lock);

	/* On récupère le premier bloc libre d'une taille suffisante */
	struct fb* bl = (*strategy)(mem_ll.next, taille_align);

	/* Si bl est NULL, on a pas de zone assez grande pour l'allocation */
	if (bl == NULL) {
		pthread_mutex_unlock(&lock);
		return NULL;
	}

	/*
	 * On sépare notre zone libre et on créé notre nouvelle zone libre
	 * à bl + taille_align
	 * Sauf si celle ci est inférieur au padding au quel cas toute la zone libre
	 * est occupée.
	 */
	struct fb* next = NULL;
	if (bl->size - taille_align < sizeof(struct fb)) {
		taille_align = bl->size;

		/* Le suivant de la zone libre précédente sera donc la zone libre d'après */
		next = bl->next;
	} else {
		struct fb *new_bl = (struct fb*)((char*)bl + taille_align);
		new_bl->size = bl->size - taille_align;
		new_bl->next = bl->next;

		/* Le suivant de la zone libre précédente sera donc la zone actuelle */
		next = new_bl;
	}

	/* On relie ici nos zones libres */
	struct fb* prec = &mem_ll;
	while(prec->next != bl) {
		prec = prec->next;
	}
	prec->next = next;
	
	/* On marque la taille de la zone occupé dans notre bloc occupé */
	struct bb *bo = (struct bb*)bl;
	bo->size = taille_align;

	/* On marque notre valeur de débordement */
	long *debordement = (long*) ((char*)bl + taille_align - sizeof(long));
	*debordement = DEBORDEMENT;

	/* On libère notre mutex car on a fini */
	pthread_mutex_unlock(&lock);

	/* On renvoie le pointeur au début de la zone + 1*sizeof(struct bb) */
	return (void*)(bo+1);
}

void mem_free(void *zone) {
	/* Si le pointeur envoyé est NULL on ne fait rien */
	if (zone == NULL) {
		return;
	}

	/* On vérrouille cette partie pour empêcher une allocation simultanée */
	pthread_mutex_lock(&lock);

	/* On se replace en début de zone et on récupère sa taille */
	struct fb* debut = (struct fb*)((struct bb*)zone - 1);
	size_t taille = ((struct bb*)debut)->size;

	/* On regarde si il y a eu débordement, si c'est le cas on abort le programme */
	long *debordement = (long*) ((char*)debut + taille - sizeof(long));
	if (*debordement != DEBORDEMENT) {
		perror("Dépassement de la mémoire alloué détecté !\n");
		abort();
	}

	/* On récupère la zone libre précédente */
	struct fb* prec = &mem_ll;
	while(prec->next != NULL && prec->next < debut) {
		prec = prec->next;
	}

	/*
	 * Si la zone libre précédente est différente de mem_ll
	 * et qu'elle est juste à gauche de la zone à libérer
	 */
	if (prec != &mem_ll && (struct fb*)((char*)prec + prec->size) == debut) {
		/* On ajoute à la taille de prec celle de la zone à libérer */
		prec->size += taille;

		/* Si la zone juste à droite de la zone à libérer est aussi une zone libre */
		if (prec->next != NULL && (char*)prec + prec->size == (char*)prec->next) {
			/*
			 * On ajoute la taille de cette zone à celle de gauche et son suivant 
			 * va devenir le suivant de la zone de gauche
			 */
			prec->size += prec->next->size;
			prec->next = prec->next->next;
		}
	} else {
		/* Sinon on créé notre nouvelle zone libre */
		debut->size = taille;
		debut->next = prec->next;

		/* Si la zone juste à droite est une zone libre */
		if (prec->next != NULL && (char*)debut + taille == (char*)prec->next) {
			/*
			 * On ajoute la taille de cette zone à la nouvelle zone et son suivant 
			 * va devenir le suivant la nouvelle zone
			 */
			debut->size += prec->next->size;
			debut->next = prec->next->next;
		}

		/* On fait pointer prec->next sur la zone créé */
		prec->next = debut;
	}

	/* On libère notre mutex */
	pthread_mutex_unlock(&lock);
}

size_t mem_get_size(void *zone) {
	/*
	 * On recule le pointeur de 1*sizeof(struct bb) pour récupérer la taille de la zone
	 * Puis on enlève sizeof(struc bb) pour avoir la taille exact allouée
	 * Puis on enlève aussi la taille d'une zone de débordement
	 */
	return (((struct bb*)zone-1)->size - sizeof(struct bb) - sizeof(long));
}

void mem_show(void (*print)(void *zone, size_t taille, int free)) {
	/* On parcours notre zone mémoire pour afficher son contenu */
	char* parcours_mem = mem_begin;
	struct fb* parcours_ll = mem_ll.next;

	/* On parcours les zones en mémoire en vérifiant si celles-ci sont libres ou non */
	while(parcours_mem < mem_begin + mem_size) {
		/* On cherche ici une zone libre correspondante */
		while(parcours_ll != NULL && parcours_ll < (struct fb*)parcours_mem) {
			parcours_ll = parcours_ll->next;
		}

		/* 
		 * Si les adresses sont les mêmes alors c'est une zone libre
		 * Sinon on est sur une zone occupée
		 */
		if (parcours_ll == (struct fb*)parcours_mem) {
			print((void*)parcours_ll, parcours_ll->size, 1);
		} else {
			print((void*)parcours_mem, ((struct bb*)parcours_mem)->size, 0);
		}

		parcours_mem = parcours_mem + ((struct bb*)parcours_mem)->size;
	}
}

void mem_fit(mem_fit_function_t *function) {
	/* On affecte à notre variable de stratégie la fonction à utiliser */
	strategy = function;
}

struct fb* mem_fit_first(struct fb* liste, size_t taille) {
	/* On parcours notre liste de zones libres tant que la zone n'est pas assez grande */
	struct fb* parcours = liste;

	while(parcours != NULL && parcours->size < taille) {
		parcours = parcours->next;
	}

	/*
	 * Si parcours est NULL, on a pas de zone assez grande.
	 * Sinon, on a trouvé la première zone assez grande
	 */
	return parcours;
}

struct fb* mem_fit_best(struct fb* liste, size_t taille) {
	/* On parcours toute notre liste pour récupérer la zone avec le plus petit résidu */
	struct fb* parcours = liste;
	struct fb* plusPetit = NULL;

	while(parcours != NULL) {
		/* Si la zone qu'on parcours est plus petite que plusPetit on prend cette zone */
		if (parcours->size >= taille && (plusPetit == NULL || parcours->size < plusPetit->size)) {
			plusPetit = parcours;
		}
		parcours = parcours->next;
	}

	/* On renvoie le résultat */
	return plusPetit;
}

struct fb* mem_fit_worst(struct fb* liste, size_t taille) {
	/* On parcours toute notre liste pour récupérer la zone avec le plus grand résidu */
	struct fb* parcours = liste;
	struct fb* plusGrand = NULL;

	while(parcours != NULL) {
		/* Si la zone qu'on parcours est plus grande que plusGrand on prend cette zone */
		if (parcours->size >= taille && (plusGrand == NULL || parcours->size > plusGrand->size)) {
			plusGrand = parcours;
		}
		parcours = parcours->next;
	}

	/* On renvoie le résultat */
	return plusGrand;
}