#include <stdio.h>
#include <stdlib.h>

#ifndef DEFINE_LISTE
#define DEFINE_LISTE

typedef struct struct_cell_libre{
    int adresse;
    int taille;
    struct struct_cell_libre* suivant;
    struct struct_cell_libre* precedent;
}cell_libre;

typedef cell_libre* liste_libre;

liste creer_liste();
int estVide(liste l);
int inserer_element(liste *l, int adresse, int taille);
int supprimer_element(liste *l, int adresse, int taille);
//void affiche_liste(liste l);

#endif
