/*
 fichier definissant les sources des fonctions :
 	-d'allocation mémoire
 	-de libération mémoire
 
 F.Bigard le 06/01/2013
*/

#include "allocation.h"

/*fonction permettant d'allouer dynamiquement avec gestion d'erreur */
void *allocation(int nombre, size_t taille){
  void *pt = NULL;
  pt = malloc(nombre*taille);
  if(pt == NULL){
    fprintf(stderr, "Erreur d'allocation pour %d element de taille %d\n", nombre, sizeof(taille));
    exit(EXIT_FAILURE);
  }
  return pt;
}




void libere(void **pt){
  if(*pt != NULL)
    free(*pt);
  *pt = NULL;
}
