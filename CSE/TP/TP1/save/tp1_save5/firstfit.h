/*
    fonctions permettant de simuler l'algorithme firstfit
    Florian Bigard
    Le 23 fév.
*/




#ifndef DEFINE_FIRSTFIT
#define DEFINE_FIRSTFIT

#include <stdio.h>
#include <stdlib.h>
#include "fonction_generale.h"

int allouer_ff(int t, liste *l_libre, liste *l_occupe, int c);
int insere_occupe_ff(int a, int t, liste *l_occupe);

int supprime_occupe_ff(int t, liste *l_occupe, liste *l_libre);
liste liberer_ff(int a, int t, liste *l_libre);

void fusion_ff(liste prec, liste act, liste suiv);
int compacter_ff(int t, liste *l_occupe, liste *l_libre);

void afficher_ff(liste l_libre, liste l_occupe);

int initialiser_ff(liste *l_libre, liste *l_occupe);

#endif
