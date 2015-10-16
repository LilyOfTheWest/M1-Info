/*
    fonctions permettant de simuler l'algorithme bestfit
    Florian Bigard
    Le 23 fév.
*/




#ifndef DEFINE_BESTFIT
#define DEFINE_BESTFIT

#include <stdio.h>
#include <stdlib.h>
#include "fonction_generale.h"

int allouer_bf(int t, liste *l_libre, liste *l_occupe, int c);
int insere_occupe_bf(int a, int t, liste *l_occupe);

int supprime_occupe_bf(int t, liste *l_occupe, liste *l_libre);
liste liberer_bf(int a, int t, liste *l_libre);

void fusion_bf(liste prec, liste act, liste suiv);
int compacter_bf(int t, liste *l_occupe, liste *l_libre);

void afficher_bf(liste l_libre, liste l_occupe);

int initialiser_bf(liste *l_libre, liste *l_occupe);

#endif