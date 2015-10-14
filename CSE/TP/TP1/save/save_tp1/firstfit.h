#include <stdio.h>
#include <stdlib.h>

#ifndef DEFINE_LISTE
#define DEFINE_LISTE

typedef struct struct_cell{
    int adresse;
    int taille;
    struct struct_cell* suivant;
}cell;

typedef cell* liste;


int initialiser_ff(liste *l_libre, liste *l_occupe);
int allouer_ff(int t, liste *l_libre, liste *l_occupe);
void afficher_ff(liste l_libre, liste l_occupe);
int liberer_ff(int a, int t, liste *l_libre, liste *l_occupe);
liste creer_noeud_ll(int adresse, int taille, liste precedent, liste suivant);
void fusion_ff(liste pre, liste act, liste suiv);
int insere_occupe(int a, int t, liste *l_occupe);
int supprime_occupe(int a, liste *l_occupe, liste *l_libre);
int choisi_desallocation(liste l_occupe);
int choisi_allocation();

#endif
