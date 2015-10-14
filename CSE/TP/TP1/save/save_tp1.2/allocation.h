/*
 fichier definissant les headers des fonctions :
 	-d'allocation mémoire
 	-de libération mémoire
 
 F.Bigard le 06/01/2013
*/


#ifndef DEF_ALLOCATION
#define DEF_ALLOCATION

#include <stdlib.h>
#include <stdio.h>

void *allocation(int nombre, size_t taille);
void libere(void **pt);

#endif
