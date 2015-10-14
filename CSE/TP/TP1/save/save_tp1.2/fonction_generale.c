#include "fonction_generale.h"
#include "allocation.h"


//fonction permettant de créer un noeud selon un adresse, une taille, un precedent et un suivant
liste creer_noeud(int adresse, int taille, liste precedent, liste suivant){
    liste l = allocation(1, sizeof(cell));
    l->adresse = adresse;
    l->taille = taille;
    l->suivant = suivant;
    l->precedent = precedent;

    return l;
}



//fonction permettant d'initialiser une liste libre et une liste occupee
int initialiser(liste *l_libre, liste *l_occupe){
    *l_libre = allocation(1, sizeof(cell));

    (*l_libre)->adresse = 0;
    (*l_libre)->taille = 2000;
    (*l_libre)->suivant = NULL;
    (*l_libre)->precedent = NULL;

    //la liste occupee est vide au tout début, donc pointeur null
    *l_occupe = NULL;

    return 1;
}


//fonction permettant de choisir au hasard une desallocation selon une liste occupée
int choisi_desallocation(liste l_occupe){
    int i = rand()%100;
    liste it = l_occupe;

    while(i>0){
        if(it == NULL){
            it = l_occupe;
        }
        else{
            it = it->suivant;
        }
        i--;
    }

    if(it == NULL)
        return 0;

    return it->adresse;
}


//fonction permettant de choisir une allocation au hasard 
int choisi_allocation(){
    int i = rand()%500;
    i = (i/10)*10; //on divise par 10 puis on remultiplie le résultat par 10 pour avoir un nombre de Mo divisible par 10 (plus clair)
    i += 10; //on rajoute 10 pour ne pas avoir 0 comme allocation

    return i;
}
