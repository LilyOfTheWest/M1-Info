#include "nextfit.h"
#include "allocation.h"


//fonction permettant d'initialiser une liste libre et une liste occupee
int initialiser_nf(liste *l_libre, liste *l_occupe){
    *l_libre = allocation(1, sizeof(cell));

    (*l_libre)->adresse = 0;
    (*l_libre)->taille = 2000;
    (*l_libre)->suivant = *l_libre;
    (*l_libre)->precedent = *l_libre;

    //la liste occupee est vide au tout début, donc pointeur null
    *l_occupe = NULL;

    return 1;
}

//fonction permettant de fusionner les listes libres si elles sont adjacentes
void fusion_nf(liste prec, liste act, liste suiv){
    if(act->suivant != act){ //si il n'y a pas qu'une zone libre dans la liste libre
        //fusion de celle de droite et celle de gauche avec celle du milieu
        if(prec->taille + act->taille == suiv->adresse - prec->adresse){
            prec->taille = prec->taille + act->taille + suiv->taille;
            prec->suivant = suiv->suivant;
            (prec->suivant)->precedent = prec;
            free(suiv);
            free(act);
        }
        else{
            if(prec->taille == act->adresse - prec->adresse){ //fusion de l'actuel et du precedent
                prec->taille = prec->taille + act->taille;
                prec->suivant = act->suivant;
                (prec->suivant)->precedent = prec;
                free(act);
            }
            if(act->taille == suiv->adresse - act->adresse){ //fusion de l'actuel et du suivant
                act->taille = act->taille + suiv->taille;
                act->suivant = suiv->suivant;
                (act->suivant)->precedent = prec;
                free(suiv);
            }
        }
    }
}


//fonction permettant d'insérer un processus dans la liste occupee selon une taille et une adresse
int insere_occupe_nf(int a, int t, liste *l_occupe){
    liste it_occupe = *l_occupe;

    //si la liste est vide alors on créé simplement un noeud sans suivant
    if(it_occupe == NULL){
        *l_occupe = creer_noeud(a, t, NULL, NULL);
        return 1;
    }
    //si la premiere cellule de la liste a déjà une adresse supérieure à celle qu'on veut mettre, alors on créé un noeud au tout début de la liste
    else if(it_occupe->adresse >= a){
        *l_occupe = creer_noeud(a, t, NULL, it_occupe);
        it_occupe->precedent = *l_occupe;
        return 1;
    }
    else{
        //sinon on parcours notre liste tant qu'on est pas arrivé à la fin et que l'adresse est inférieure
        while(it_occupe->suivant != NULL && (it_occupe->suivant)->adresse < a){
            it_occupe = it_occupe->suivant;
        }

        //on est arrivé à la fin de la liste, on rajoute donc une cellule
        if(it_occupe->suivant == NULL){
            it_occupe->suivant = creer_noeud(a, t, it_occupe, NULL);
            return 1;
        }
        //sinon on insere une noeud entre it_occupe et it_occupe->suivant
        else{
            it_occupe->suivant = creer_noeud(a, t, it_occupe, it_occupe->suivant);
            ((it_occupe->suivant)->suivant)->precedent = it_occupe->suivant;
            return 1;
        }
    }
}


//fonction permettant d'ajouter une liste libre selon une adresse, une taille, une liste libre et une liste occupée
liste liberer_nf(int a, int t, liste *l_libre){
    liste it_libre = *l_libre;
    liste fin = NULL;

    //si la liste libre est vide alors on créé simplement un noeud
    if(it_libre == NULL){
        *l_libre = creer_noeud(a, t, NULL, NULL);
        (*l_libre)->precedent = *l_libre;
        (*l_libre)->suivant = *l_libre;
        it_libre = *l_libre;
        fprintf(stderr, "je créé un noeud à l'adresse %d de taille %d avec precedent %d et suivant %d", a, t, it_libre->adresse, (it_libre->suivant)->adresse);
        return *l_libre;
    }
    //sinon si la première cellule a déjà une adresse supérieure à celle qu'on veut mettre, on créé un zone libre au tout début de la liste
    else if(it_libre->adresse >= a){
        *l_libre = creer_noeud(a, t, it_libre->precedent, it_libre); 
        (it_libre->precedent)->suivant = *l_libre;
        it_libre->precedent = *l_libre;

        //on fusionne éventuellement les zones libres adjacents
        fusion_nf((*l_libre)->precedent, *l_libre, (*l_libre)->suivant);
            fprintf(stderr, "je créé un noeud à l'adresse %d de taille %d avec precedent %d et suivant %d", a, t, it_libre->adresse, (it_libre->suivant)->adresse);

        return *l_libre;
    }
    else{

        fin = it_libre->suivant;
        it_libre = it_libre->suivant;

        //on se déplace pour trouver l'endroit ou il faut mettre notre zone
        while(it_libre->suivant != fin && (it_libre->suivant)->adresse < a){
            it_libre = it_libre->suivant;
        }

        if(it_libre->suivant == fin){ 
            it_libre->suivant = creer_noeud(a, t, it_libre, fin); 
            fin->precedent = it_libre->suivant;

            fusion_nf(it_libre, it_libre->suivant, (it_libre->suivant)->suivant);
            fprintf(stderr, "je créé un noeud à l'adresse %d de taille %d avec precedent %d et suivant %d", a, t, it_libre->adresse, (it_libre->suivant)->adresse);

            return it_libre->suivant;
        }
        else{
            //sinon on insere une zone libre entre deux noeuds et on fusionne éventuellement les zones libres adjacents
            it_libre->suivant = creer_noeud(a, t, it_libre, it_libre->suivant); 
            fprintf(stderr, "je créé un noeud à l'adresse %d de taille %d avec precedent %d et suivant %d", a, t, it_libre->adresse, (it_libre->suivant)->adresse);
            ((it_libre->suivant)->suivant)->precedent = it_libre->suivant;

            fusion_nf(it_libre, it_libre->suivant, (it_libre->suivant)->suivant);

            return it_libre->suivant;
        }
    }

}


//l_occupe contient l'adresse du bloc occupé juste après celui qui a été supprimé, l_libre contient la liste qui vient d'être allouée
int compacter_nf(liste l_occupe, liste *l_libre, liste zone_libere){
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
int supprime_occupe_nf(int a, liste *l_occupe, liste *l_libre, int c){
    liste it_occupe = *l_occupe;
    liste it_occupe2;
    liste it_libre;

    //si la liste est vide il n'y a rien a supprimer on retourne 0
    if(it_occupe == NULL){
        //fprintf(stderr, "Pas de bloc occupé, on peut rien supprimer \n");
        return 0;
    }
    //sinon si la première cellule est la bonne
    else if(it_occupe->adresse == a){
        //fprintf(stderr, "Premier bloc à supprimer, on le supprime \n");
        //on créé une liste libre
        it_libre = liberer_nf(a, it_occupe->taille, l_libre);
        //on supprime le premier noeud
        *l_occupe = it_occupe->suivant;
        (*l_occupe)->precedent = NULL;
        free(it_occupe);


        if(c != 0){
            it_occupe = (*l_occupe)->suivant;
            compacter_nf(it_occupe, l_libre, it_libre);
        }


        return 1;
    }
    else{
        //fprintf(stderr, "On a trouvé le bloc au milieu ou a la fin, on va le supprimer \n");
        //on  cherche l'adresse tant qu'on est pas arrivé jusqu'à la fin
        while(it_occupe->suivant != NULL && (it_occupe->suivant)->adresse != a){
            it_occupe = it_occupe->suivant;
        }

        if(it_occupe->suivant == NULL){
            return 0;
        }
        else{ // on a trouvé la bonne zone

            //fprintf(stderr, "On a trouvé le bloc au milieu ou a la fin, on va le supprimer \n");
            //sinon on créé une liste libre
            it_libre = liberer_nf(a, (it_occupe->suivant)->taille, l_libre);

            if(it_occupe->suivant->suivant == NULL){//on veut supprimer le dernier noeud
                free(it_occupe->suivant);
                it_occupe->suivant = NULL;
            }
            else{//on supprimer un noeud quelconque

                //on supprime le noeud
                it_occupe2 = it_occupe->suivant;
                it_occupe->suivant = it_occupe2->suivant;

                (it_occupe2->suivant)->precedent = it_occupe->suivant;
                free(it_occupe2);
            }

            if(c != 0){
                it_occupe = it_occupe->suivant;
                compacter_nf(it_occupe, l_libre, it_libre);
            }

            return 1;
        }
    }
}




//fonction permettant d'allouer une taille selon une liste libre et une liste occupee
int allouer_nf(int t, liste *l_libre, liste *l_occupe){
    liste it_libre = *l_libre;
    liste it_libre2;
    liste fin;

    if(it_libre == NULL){ // si on a pas de liste libre alors on retourne 0 car on ne peut rien allouer
        return 0;
    }
    else if(it_libre->taille >= t){ // si la première cellule de la liste convient alors on la prend
        //on insere selon l'adresse trouvée dans la liste occupee le processus
        insere_occupe_nf(it_libre->adresse, t, l_occupe);

        //on soustrait à la zone libre la taille allouée et on change son adresse
        it_libre->adresse = it_libre->adresse + t;
        it_libre->taille = it_libre->taille - t;

        //si la taille est devenu nulle on supprime la zone libre
        if(it_libre->taille == 0){
            (*l_libre) = (*l_libre)->suivant;
            (*l_libre)->precedent = it_libre->precedent;
            (it_libre->precedent)->suivant = *l_libre;
            free(it_libre);
        }

        return 1;
    }
    else{
        fin = it_libre;

        // on se déplace jusqu'à trouver une zone libre qui convient
        while(it_libre->suivant != fin && (it_libre->suivant)->taille < t){
            it_libre = it_libre->suivant;
        }

        //on a trouvé la bonne zone

        if(it_libre->suivant == fin){ // pas trouvé de zone libre
            return 0;
        }
        else{
            //sinon alors on insere un occupée à l'adresse trouvée et selon la taille donnée
            insere_occupe_nf((it_libre->suivant)->adresse, t, l_occupe);

            //on met à jour la zone libre
            (it_libre->suivant)->adresse = (it_libre->suivant)->adresse + t;
            (it_libre->suivant)->taille = (it_libre->suivant)->taille - t;

            //si la zone libre contient une taille nulle alors on la supprime
            if((it_libre->suivant)->taille == 0){
                it_libre2 = it_libre->suivant;
                it_libre->suivant = (it_libre->suivant)->suivant;
                ((it_libre->suivant)->suivant)->precedent = it_libre->suivant;
                free(it_libre2);
            }

            return 1;
        }
    }
}




/*
//fonction permettant d'anficher correctement le contenu de la liste libre et de la liste occupée de façon a représenter un tas (schématiquement)
void afficher_nf(liste l_libre, liste l_occupe){
    liste it_libre = l_libre;
    liste it_occupe = l_occupe;
    liste fin = it_libre;
    int continuer_libre = 1;

    //on affiche le premier libre dans l'ordre avec les occupés
    while(it_libre && continuer_libre != 0 && it_occupe != NULL){
        if(it_libre->adresse < it_occupe->adresse){
            printf("---(libre -> %d %d %d)---", it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille));
            continuer_libre = 0;
            it_libre = it_libre->suivant;
        }
        else{
            printf("---(occupe -> %d %d %d)---", it_occupe->adresse, it_occupe->taille, (it_occupe->adresse+it_occupe->taille));
            it_occupe = it_occupe->suivant;
        }
        //fprintf(stderr, "Je suis dans le début\n");
    }

    if(continuer_libre == 1){ //on a pas utilisé la première case de liste libre
        printf("---(libre -> %d %d %d)---", it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille));
        continuer_libre = 0;
        it_libre = it_libre->suivant;
    }

    if(it_libre != it_libre->suivant){// si il ne s'agissait pas d'un singleton
        //on affiche les deux listes donc l'ordre
        while(it_libre && it_libre->suivant != fin && it_occupe != NULL){
            if((it_libre->suivant)->adresse < it_occupe->adresse){
                printf("---(libre -> %d %d %d)---", (it_libre->suivant)->adresse, (it_libre->suivant)->taille, ((it_libre->suivant)->adresse + (it_libre->suivant)->taille));
                it_libre = it_libre->suivant;
            }
            else{
                printf("---(occupe -> %d %d %d)---", it_occupe->adresse, it_occupe->taille, (it_occupe->adresse+it_occupe->taille));
                it_occupe = it_occupe->suivant;
            }
        }

        //printf("Continuer vaut %d, it_libre vaut %p et fin vaut %p\n", continuer_libre, it_libre, fin);

            //fprintf(stderr, "Je suis dans l'union\n");
        while(it_libre && it_libre->suivant != fin){
            printf("---(libre -> %d %d %d)---", (it_libre->suivant)->adresse, (it_libre->suivant)->taille, ((it_libre->suivant)->adresse + (it_libre->suivant)->taille));
            it_libre = it_libre->suivant;
            //fprintf(stderr, "Je suis dans it_libre\n");
        }
    }

        while(it_occupe){
            printf("---(occupe -> %d %d %d)---", it_occupe->adresse, it_occupe->taille, (it_occupe->adresse+it_occupe->taille));
            it_occupe = it_occupe->suivant;
            //fprintf(stderr, "Je suis dans it_occupe\n");
        }
    

}
*/

void afficher_nf(liste l_libre, liste l_occupe){
    liste it_libre = l_libre;
    liste it_occupe = l_occupe;
    liste fin = it_libre;

    if(l_libre){
        do{
            printf("---(libre -> %d %d %d)---", it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille));
            it_libre = it_libre->suivant;
        }while(it_libre != fin);
    }
    else{
        printf("Pas de libre :(\n");
    }   

    printf("\n\n\n");

    if(l_occupe){
        while(it_occupe){
            printf("---(occupe -> %d %d %d)---", it_occupe->adresse, it_occupe->taille, (it_occupe->adresse+it_occupe->taille));
            it_occupe = it_occupe->suivant;
        }
    }
    else{
        printf("Pas d'occupés \n");
    }
}




