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

void fusion_bf(liste *l_libre, liste act, liste prec);
void fusion_bf_prec(liste *l_libre, liste act, liste prec);
void fusion_bf_suiv(liste *l_libre, liste act, liste prec);

int compacter_bf(int t, liste *l_occupe, liste *l_libre);

void afficher_bf(liste l_libre, liste l_occupe);

int initialiser_bf(liste *l_libre, liste *l_occupe);

liste inserer_libre_trie(liste *l_libre, liste act);

#endif
