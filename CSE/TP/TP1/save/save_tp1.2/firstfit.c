#include "firstfit.h"
#include "allocation.h"


//fonction permettant de fusionner les listes libres si elles sont adjacentes
void fusion_ff(liste prec, liste act, liste suiv){
    //fusion de celle de droite et celle de gauche avec celle du milieu
    if(prec != NULL && act != NULL && suiv != NULL && prec->taille + act->taille == suiv->adresse - prec->adresse){
        prec->taille = prec->taille + act->taille + suiv->taille;
        prec->suivant = suiv->suivant;
        free(suiv);
        free(act);
    }
    else{
        if(prec != NULL && act != NULL && prec->taille == act->adresse - prec->adresse){ //fusion de l'actuel et du precedent
            prec->taille = prec->taille + act->taille;
            prec->suivant = act->suivant;
            free(act);
        }
        if(act != NULL && suiv != NULL && act->taille == suiv->adresse - act->adresse){ //fusion de l'actuel et du suivant
            act->taille = act->taille + suiv->taille;
            act->suivant = suiv->suivant;
            free(suiv);
        }
    }

}


//fonction permettant d'insérer un processus dans la liste occupee selon une taille et une adresse
int insere_occupe_ff(int a, int t, liste *l_occupe){
    liste it_occupe = *l_occupe;

    //si la liste est vide alors on créé simplement un noeud sans suivant
    if(it_occupe == NULL){
        *l_occupe = creer_noeud(a, t, NULL, NULL);
        return 1;
    }
    //si la premiere cellule de la liste a déjà une adresse supérieure à celle qu'on veut mettre, alors on créé un noeud au tout début de la liste
    else if(it_occupe->adresse >= a){
        *l_occupe = creer_noeud(a, t, NULL, it_occupe);
        return 1;
    }
    else{
        //sinon on parcours notre liste tant qu'on est pas arrivé à la fin et que l'adresse est inférieure
        while(it_occupe->suivant != NULL && (it_occupe->suivant)->adresse < a){
            it_occupe = it_occupe->suivant;
        }

        //on est arrivé à la fin de la liste, on rajoute donc une cellule
        if(it_occupe->suivant == NULL){
            it_occupe->suivant = creer_noeud(a, t, NULL, NULL);
            return 1;
        }
        //sinon on insere une noeud entre it_occupe et it_occupe->suivant
        else{
            it_occupe->suivant = creer_noeud(a, t, NULL, it_occupe->suivant);
            return 1;
        }
    }
}

//fonction permettant d'ajouter une liste libre selon une adresse, une taille, une liste libre et une liste occupée
liste liberer_ff(int a, int t, liste *l_libre){
    liste it_libre = *l_libre;
    liste it_libre2 = NULL;

    //si la liste libre est vide alors on créé simplement un noeud
    if(it_libre == NULL){
        *l_libre = creer_noeud(a, t, NULL, NULL);
        return *l_libre;
    }
    //sinon si la première cellule a déjà une adresse supérieure à celle qu'on veut mettre, on créé un zone libre au tout début de la liste
    else if(it_libre->adresse >= a){
        *l_libre = creer_noeud(a, t, NULL, it_libre); 

        //on fusionne éventuellement les zones libres adjacents
        fusion_ff(NULL, *l_libre, (*l_libre)->suivant);

        return *l_libre;
    }
    else{
        //on se déplace pour trouver l'endroit ou il faut mettre notre zone
        while(it_libre->suivant != NULL && (it_libre->suivant)->adresse < a){
            it_libre = it_libre->suivant;
        }

        //si le suivant est null on est à la fin de la liste donc on rajoute simplement un noeud à la fin de la liste libre et on fusionne les zone libres adjacents
        if(it_libre->suivant == NULL){ 
            it_libre->suivant = creer_noeud(a, t, it_libre, NULL); 

            fusion_ff(it_libre, it_libre->suivant, NULL);

            return it_libre->suivant;
        }
        else{
            //sinon on insere une zone libre entre deux noeuds et on fusionne éventuellement les zones libres adjacents
            it_libre2 = it_libre->suivant;
            it_libre->suivant = creer_noeud(a, t, it_libre, it_libre2); 

            fusion_ff(it_libre, it_libre->suivant, (it_libre->suivant)->suivant);

            return it_libre->suivant;
        }
    }

}


//l_occupe contient l'adresse du bloc occupé juste après celui qui a été supprimé, l_libre contient la liste qui vient d'être allouée
int compacter_ff(liste l_occupe, liste *l_libre, liste zone_libere){
    liste it_libre_fin;
    liste it_occupe = l_occupe;

    //si it_occupe est null alors il n'y a pas de blocs occupés après la liste libre donc on quitte
    if(it_occupe == NULL)
        return 0;

    //on modifie tous les occupés suivants car on supprime le bloc libre
    while(it_occupe != NULL){
        it_occupe->adresse = it_occupe->adresse - zone_libere->taille;
        it_occupe = it_occupe->suivant;
    }

    //on cherche le dernier bloc libre
    it_libre_fin = zone_libere;
    while(it_libre_fin->suivant != NULL)
        it_libre_fin = it_libre_fin->suivant;

    //si la condition est vrai ça veut dire que la zone libre que l'on vient de libérer était la seule de la liste libre, on la déplace donc juste à l'adresse désirée. Sinon on la fusionne avec la zone libre en fin de liste
    if(it_libre_fin != zone_libere){
        it_libre_fin->adresse = it_libre_fin->adresse - zone_libere->taille;
        it_libre_fin->taille = it_libre_fin->taille + zone_libere->taille;
    
        *l_libre = it_libre_fin;
        free(zone_libere);
    }
    else{
        it_libre_fin->adresse = 2000 - it_libre_fin->taille;
        *l_libre = it_libre_fin;
    }


    return 1;
}



//fonction permettant de supprimer un cellule occupée selon une liste occupe, une adresse et une liste libre
int supprime_occupe_ff(int a, liste *l_occupe, liste *l_libre, int c){
    liste it_occupe = *l_occupe;
    liste it_occupe2;
    liste it_libre;

    //si la liste est vide il n'y a rien a supprimer on retourne 0
    if(it_occupe == NULL){
        return 0;
    }
    //sinon si la première cellule est la bonne
    else if(it_occupe->adresse == a){
        //on créé une liste libre
        it_libre = liberer_ff(a, it_occupe->taille, l_libre);
        //on supprime le premier noeud
        *l_occupe = it_occupe->suivant;
        free(it_occupe);

        it_occupe = it_occupe->suivant;

        if(c != 0)
            compacter_ff(it_occupe, l_libre, it_libre);

        return 1;
    }
    else{
        //on  cherche l'adresse tant qu'on est pas arrivé jusqu'à la fin
        while(it_occupe->suivant != NULL && (it_occupe->suivant)->adresse != a){
            it_occupe = it_occupe->suivant;
        }

        if(it_occupe->suivant == NULL){ // on a pas trouvé le programme avec l'adresse spécifiée, on retourne une erreure
            return 0;
        }
        else{
            //sinon on créé une liste libre
            it_libre = liberer_ff(a, (it_occupe->suivant)->taille, l_libre);

            //on supprime le noeud
            it_occupe2 = it_occupe->suivant;
            it_occupe->suivant = (it_occupe->suivant)->suivant;
            free(it_occupe2);

            it_occupe = it_occupe->suivant;

            if(c != 0)
                compacter_ff(it_occupe, l_libre, it_libre);

            return 1;
        }
    }
}




//fonction permettant d'allouer une taille selon une liste libre et une liste occupee
int allouer_ff(int t, liste *l_libre, liste *l_occupe){
    liste it_libre = *l_libre;
    liste it_libre2;

    if(it_libre == NULL){ // si on a pas de liste libre alors on retourne 0 car on ne peut rien allouer
        return 0;
    }
    else if(it_libre->taille >= t){ // si la première cellule de la liste convient alors on la prend
        //on insere selon l'adresse trouvée dans la liste occupee le processus
        insere_occupe_ff(it_libre->adresse, t, l_occupe);

        //on soustrait à la zone libre la taille allouée et on change son adresse
        it_libre->adresse = it_libre->adresse + t;
        it_libre->taille = it_libre->taille - t;

        //si la taille est devenu nulle on supprime la zone libre
        if(it_libre->taille == 0){
            *l_libre = (*l_libre)->suivant;
            free(it_libre);
        }

        return 1;
    }
    else{
        // on se déplace jusqu'à trouver une zone libre qui convient
        while(it_libre->suivant != NULL && (it_libre->suivant)->taille < t){
            it_libre = it_libre->suivant;
        }

        //si le suivant est null on a trouvé aucune zone libre qui convenait, on retourne un code d'erreur
        if(it_libre->suivant == NULL){
            return 0;
        }
        else{
            //sinon alors on insere un occupée à l'adresse trouvée et selon la taille donnée
            insere_occupe_ff((it_libre->suivant)->adresse, t, l_occupe);

            //on met à jour la zone libre
            (it_libre->suivant)->adresse = (it_libre->suivant)->adresse + t;
            (it_libre->suivant)->taille = (it_libre->suivant)->taille - t;

            //si la zone libre contient une taille nulle alors on la supprime
            if((it_libre->suivant)->taille == 0){
                it_libre2 = it_libre->suivant;
                it_libre->suivant = (it_libre->suivant)->suivant;
                free(it_libre2);
            }

            return 1;
        }
    }
}





//fonction permettant d'afficher correctement le contenu de la liste libre et de la liste occupée de façon a représenter un tas (schématiquement)
void afficher_ff(liste l_libre, liste l_occupe){
    liste it_libre = l_libre;
    liste it_occupe = l_occupe;

    //on affiche les deux listes donc l'ordre
    while(it_libre != NULL && it_occupe != NULL){
        if(it_libre->adresse < it_occupe->adresse){
            printf("---(libre -> %d %d %d)---", it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille));
            it_libre = it_libre->suivant;
        }
        else{
            printf("---(occupe -> %d %d %d)---", it_occupe->adresse, it_occupe->taille, (it_occupe->adresse+it_occupe->taille));
            it_occupe = it_occupe->suivant;
        }
    }
    while(it_libre){
        printf("---(libre -> %d %d %d)---", it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille));
        it_libre = it_libre->suivant;
    }
    while(it_occupe){
        printf("---(occupe -> %d %d %d)---", it_occupe->adresse, it_occupe->taille, (it_occupe->adresse+it_occupe->taille));
        it_occupe = it_occupe->suivant;
    }
}
