/*
    fonctions permettant de simuler l'algorithme bestfit
    Florian Bigard
    Le 23 fév.
*/


#ifndef DEFINE_NEXTFIT
#define DEFINE_NEXTFIT

#include <stdio.h>
#include <stdlib.h>
#include "fonction_generale.h"


int allouer_nf(int t, liste *l_libre, liste *l_occupe, int c);
int insere_occupe_nf(int a, int t, liste *l_occupe);

int supprime_occupe_nf(int t, liste *l_occupe, liste *l_libre);
liste liberer_nf(int a, int t, liste *l_libre);

void fusion_nf(liste prec, liste act, liste suiv);
int compacter_nf(int t, liste *l_occupe, liste *l_libre);

void afficher_nf(liste l_libre, liste l_occupe);

int initialiser_nf(liste *l_libre, liste *l_occupe);

#endif
