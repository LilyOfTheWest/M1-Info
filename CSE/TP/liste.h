#ifndef LISTES_H
#define LISTES_H

/****************************************************************************/
/*******************   fichier liste.h  *************************************/
/****************************************************************************/

/* Listes de type FIFO ou LIFO.
   Pour une liste LIFO (pile), utiliser empile et depile
   Pour une liste FIFO (file d'attente), utiliser enfile et defile
    rmq : depile et defile font la même chose.
*/

/* Le type des listes est "Liste" *********************/
typedef struct liste Liste;

Liste *creer_liste_vide();
/* Renvoie un pointeur sur une liste vide */

void detruit_liste(Liste *l);
/* Detruit la liste et libere la memoire utilisé par la liste */
/* Cette fonction doit être appelée à chaque fois qu'une liste
   n'est plus utilisée */

int est_vide(Liste *l);
/* Renvoie vrai si la liste l est vide */

void enfile(void *objet, Liste *l);
/* Ajoute le sommet à la fin de la liste l (FIFO) */
/* La liste l passé en paramètre est donc modifiée */

void empile(void *objet, Liste *l);
/* Ajoute le sommet au début de la liste l */
/* La liste l passé en paramètre est donc modifiée */

void *defile(Liste *l);
/* Retire le premier sommet de la liste l et le renvoie */
/* La liste l passé en paramètre est donc modifiée */
/* Appeler defile sur une liste vide plante probablement */

void *depile(Liste *l);
/* idem defile */

int taille(Liste *l);
/* Retourne le nombre d'éléments de la liste */


/* ************** Iterateur sur les listes  ********************/

typedef struct element iterateur_l;

iterateur_l *init_it(Liste *l);
/* Retourne un iterateur sur le début de la liste */
/* Plante probablement si la liste l n'est pas initialisée */

iterateur_l *suivant_it(iterateur_l *it);
/* Retourne un iterateur sur l'élément suivant */
/* Plante probablement si it n'est n'est pas initialisé ou est arrivé à la
 fin de la liste */

void *element_it(iterateur_l *it);
/* retourne l'élément pointé par l'iterateur */
/* Plante probablement si it n'est n'est pas initialisé ou est arrivé à la
 fin de la liste */

int fini_it(iterateur_l *it);
/* retourne vrai si l'iterateur est arrivé à la fin de la liste */
/* Plante probablement si it n'est n'est pas initialisé */

void supprimer_elem_it(iterateur_l *it);

#endif
