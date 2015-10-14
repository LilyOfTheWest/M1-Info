#ifndef DEFINE_FONCTION_GENERALE
#define DEFINE_FONCTION_GENERALE


#include <stdio.h>
#include <stdlib.h>


typedef struct struct_cell{
    int adresse;
    int taille;
    struct struct_cell* suivant;
    struct struct_cell* precedent;
}cell;

typedef cell* liste;


liste creer_noeud(int adresse, int taille, liste precedent, liste suivant);
int initialiser(liste *l_libre, liste *l_occupe);

int choisi_desallocation(liste l_occupe);
int choisi_allocation();
void detruire_liste(liste *l);

#endif
