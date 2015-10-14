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


//fonction permettant de choisir au hasard une desallocation (en selectionnant la taille du bloc à enlever) selon une liste occupée
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

    return it->taille;
}


//fonction permettant de choisir une allocation au hasard entre 10Mo et 510Mo
int choisi_allocation(){
    int i = rand()%500;
    i = (i/10)*10; //on divise par 10 puis on remultiplie le résultat par 10 pour avoir un nombre de Mo divisible par 10 (plus clair)
    i += 10; //on rajoute 10 pour ne pas avoir 0 comme allocation

    return i;
}


//fonction permettant de désallouer complètement une liste
void detruire_liste(liste *l){
    liste it = *l;
    liste it2;
    liste fin = *l;

    if(*l == NULL)
        return;

    while(it->suivant && it->suivant != fin){
        it2 = it->suivant; //prochaine destinatation
        free(it);
        it = it2;
    }
        
    free(it);
    

    *l = NULL;

    printf("\n\n\n\n");
}
        
