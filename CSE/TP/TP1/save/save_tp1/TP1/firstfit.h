#include <stdio.h>
#include <stdlib.h>


typedef struct struct_cell{
    int adresse;
    int taille;
    struct struct_cell* suivant;
    struct struct_cell* precedent;
}cell;

typedef cell* liste;


liste creer_noeud_ll(int adresse, int taille, liste precedent, liste suivant);
void fusion_ff(liste prec, liste act, liste suiv);
int initialiser_ff(liste *l_libre, liste *l_occupe);
int insere_occupe(int a, int t, liste *l_occupe);
liste liberer_ff(int a, int t, liste *l_libre);
int compacter(liste l_occupe, liste *l_libre, liste zone_libere);
int supprime_occupe(int a, liste *l_occupe, liste *l_libre, int c);
int allouer_ff(int t, liste *l_libre, liste *l_occupe);
void afficher_ff(liste l_libre, liste l_occupe);
int choisi_desallocation(liste l_occupe);
int choisi_allocation();
