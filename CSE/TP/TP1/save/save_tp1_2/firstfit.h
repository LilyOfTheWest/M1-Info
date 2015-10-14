#ifndef DEFINE_FIRSTFIT
#define DEFINE_FIRSTFIT

#include <stdio.h>
#include <stdlib.h>
#include "fonction_generale.h"

int allouer_ff(int t, liste *l_libre, liste *l_occupe);
int insere_occupe_ff(int a, int t, liste *l_occupe);

int supprime_occupe_ff(int a, liste *l_occupe, liste *l_libre, int c);
liste liberer_ff(int a, int t, liste *l_libre);

void fusion_ff(liste prec, liste act, liste suiv);
int compacter_ff(liste l_occupe, liste *l_libre, liste zone_libere);

void afficher_ff(liste l_libre, liste l_occupe);

int initialiser_ff(liste *l_libre, liste *l_occupe);

#endif
