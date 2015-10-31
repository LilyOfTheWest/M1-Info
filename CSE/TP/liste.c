#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

/* Vous n'avez pas besoin de regarder ce fichier.
   Lisez liste.h */

/* Listes de type Fifo (fist in, first out) ou LIFO */
struct element {
  void *objet;
  struct element *suivant;
  struct element *precedent;
};

struct liste {
  struct element *premier;
  struct element *dernier;
  int taille;
};

Liste *creer_liste_vide() {
  /* renvoie une liste vide */
  Liste *l;

  l = malloc(sizeof(struct liste));
  l->taille = 0;
  l->premier = NULL;
  l->dernier = NULL;
  return l;
}

void detruit_liste(Liste *l) {
  /* detruit la liste et libere la memoire utilis� par la liste */
  while (! est_vide(l)) defile(l);
  free(l);
}

int est_vide(Liste *l) {
  /* renvoie vrai si la liste l est vide */
  return (l->taille == 0);
}

void enfile(void *objet, Liste *l) {
  /* ajoute le sommet � la fin de la liste l */
  struct element *e;

  e = malloc(sizeof(struct element));
  e->objet = objet;
  e->suivant = NULL;
  e->precedent = NULL;
  if (l->taille == 0)
    l->premier = l->dernier = e;
  else {
    (l->dernier)->suivant = e;
    e->precedent = l->dernier;
    l->dernier = e;
  }
  (l->taille)++;
}

void empile(void *objet, Liste *l) {
  /* ajoute le sommet au debut de la liste l */
  struct element *e;

  e = malloc(sizeof(struct element));
  e->objet = objet;
  e->suivant = l->premier;
  e->precedent = NULL;
  l->premier = e;
  if (l->taille == 0) l->dernier = e;
  (l->taille)++;
}

/* appeler defile sur une liste vide plante probablement */
void *defile(Liste *l) {
  /* retire le premier sommet de la file l et le renvoie */
  void *objet;
  struct element *deuxieme;

  objet = (l->premier)->objet;
  deuxieme = (l->premier)->suivant;
  free(l->premier);
  (l->premier)->precedent = NULL;
  l->premier = deuxieme;
  (l->taille)--;
  return objet;
}

void *depile(Liste *l) {
  return defile(l);
}

int taille(Liste *l) {
  /* retourne le nombre d'�l�ments de la liste */
  return l->taille;
}



/* ************** Iterateur sur les listes  ********************/


iterateur_l *init_it(Liste *l){
  /* retourne un iterateur sur le 1er element de la liste */
  return (iterateur_l *) l->premier;
}


iterateur_l *suivant_it(iterateur_l *it){
  return (iterateur_l *) it->suivant;
}

void *element_it(iterateur_l *it){
  return it->objet;
}

int fini_it(iterateur_l *it){
  return (it == NULL);
}

void supprimer_elem_it(iterateur_l *it) {
    (it->precedent)->suivant = it->suivant;
    (it->suivant)->precedent = it->precedent;

    free(it);
}

