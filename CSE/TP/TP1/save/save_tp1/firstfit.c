#include "firstfit.h"
#include "allocation.h"


liste creer_noeud_ll(int adresse, int taille, liste precedent, liste suivant){
    liste l = allocation(1, sizeof(cell));
    l->adresse = adresse;
    l->taille = taille;
    l->suivant = suivant;

    return l;
}


void fusion_ff(liste prec, liste act, liste suiv){
    if(prec != NULL && act != NULL && prec->taille == act->adresse - prec->adresse){ //fusion de l'actuel et du precedent
        prec->taille = prec->taille + act->taille;
        prec->suivant = act->suivant;
        free(act);
    }
    if(act != NULL && suiv != NULL && act->taille == suiv->adresse - act->adresse){ //fusion de l'actuel et du suivant
        act->taille = act->taille + suiv->taille;
        free(suiv);
    }
}

int initialiser_ff(liste *l_libre, liste *l_occupe){
    *l_libre = creer_noeud_ll(0, 2000, NULL, NULL); 

    *l_occupe = NULL;

    return 1;
}

int insere_occupe(int a, int t, liste *l_occupe){
    liste it_occupe = *l_occupe;

    if(it_occupe == NULL){
        *l_occupe = creer_noeud_ll(a, t, NULL, NULL);
        return 1;
    }
    else if(it_occupe->adresse >= a){
        *l_occupe = creer_noeud_ll(a, t, NULL, it_occupe);
        return 1;
    }
    else{
        while(it_occupe->suivant != NULL && (it_occupe->suivant)->adresse < a){
            it_occupe = it_occupe->suivant;
        }

        if(it_occupe->suivant == NULL){
            it_occupe->suivant = creer_noeud_ll(a, t, NULL, NULL);
            return 1;
        }
        else{
            it_occupe->suivant = creer_noeud_ll(a, t, NULL, it_occupe->suivant);
            return 1;
        }
    }
}

int supprime_occupe(int a, liste *l_occupe, liste *l_libre){
    liste it_occupe = *l_occupe;
    liste it_occupe2;

    if(it_occupe == NULL){
        return 0;
    }
    else if(it_occupe->adresse == a){
        liberer_ff(a, it_occupe->taille, l_libre, l_occupe);
        *l_occupe = it_occupe->suivant;
        free(it_occupe);

        return 1;
    }
    else{

        while(it_occupe->suivant != NULL && (it_occupe->suivant)->adresse != a){
            it_occupe = it_occupe->suivant;
        }

        if(it_occupe->suivant == NULL){ // on a pas trouvé le programme avec l'adresse spécifiée, on quitte le programme.
            return 0;
        }
        else{
            liberer_ff(a, (it_occupe->suivant)->taille, l_libre, l_occupe);
            it_occupe2 = it_occupe->suivant;
            it_occupe->suivant = (it_occupe->suivant)->suivant;
            free(it_occupe2);
            return 1;
        }
    }
}





int allouer_ff(int t, liste *l_libre, liste *l_occupe){
    liste it_libre = *l_libre;
    liste it_libre2;

    if(it_libre == NULL){ // si on a pas de liste libre alors on retourne 0 car on ne peut rien allouer
        return 0;
    }
    else if(it_libre->taille >= t){ // si la première cellule de la liste convient alors on la prend
        insere_occupe(it_libre->adresse, t, l_occupe);

        it_libre->adresse = it_libre->adresse + t;
        it_libre->taille = it_libre->taille - t;

        if(it_libre->taille == 0){
            *l_libre = (*l_libre)->suivant;
            free(it_libre);
        }

        return 1;
    }
    else{
        while(it_libre->suivant != NULL && (it_libre->suivant)->taille < t){
            it_libre = it_libre->suivant;
        }

        if(it_libre->suivant == NULL){
            return 0;
        }
        else{
            insere_occupe((it_libre->suivant)->adresse, t, l_occupe);

            (it_libre->suivant)->adresse = (it_libre->suivant)->adresse + t;
            (it_libre->suivant)->taille = (it_libre->suivant)->taille - t;


            if((it_libre->suivant)->taille == 0){
                it_libre2 = it_libre->suivant;
                it_libre->suivant = (it_libre->suivant)->suivant;
                free(it_libre2);
            }

            return 1;
        }
    }
}

int liberer_ff(int a, int t, liste *l_libre, liste *l_occupe){
    liste it_libre = *l_libre;
    liste it_libre2 = NULL;

    if(it_libre == NULL){
        *l_libre = creer_noeud_ll(a, t, NULL, NULL);
        return 1;
    }
    else if(it_libre->adresse >= a){
        *l_libre = creer_noeud_ll(a, t, NULL, it_libre); 
        it_libre = *l_libre;

        return 1;
    }
    else{

        while(it_libre->suivant != NULL && (it_libre->suivant)->adresse < a){
            it_libre = it_libre->suivant;
        }

        if(it_libre->suivant == NULL){ // on se situe tout au bout de la liste
            it_libre->suivant = creer_noeud_ll(a, t, NULL, NULL); 

            fusion_ff(it_libre, it_libre->suivant, NULL);

            return 1;
        }
        else{
            it_libre2 = it_libre->suivant;
            it_libre->suivant = creer_noeud_ll(a, t, NULL, it_libre2); 

            fusion_ff(it_libre, it_libre->suivant, (it_libre->suivant)->suivant);

            return 1;
        }
    }

}




void afficher_ff(liste l_libre, liste l_occupe){
    liste it_libre = l_libre;
    liste it_occupe = l_occupe;

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


/*
   void afficher_ff(liste l_libre, liste l_occupe){
   liste it_libre = l_libre;
   liste it_occupe = l_occupe;

   if(it_libre == NULL){
   printf("Pas de liste libre !\n");
   }
   else{
   while(it_libre != NULL){
   printf("Liste libre : à l'adresse %d avec une taille de %d\n", it_libre->adresse, it_libre->taille);
   it_libre = it_libre->suivant;
   }
   }

   if(it_occupe == NULL){
   printf("Pas de liste occupée !\n");
   }
   else{
   while(it_occupe != NULL){
   printf("Liste occupée : à l'adresse %d avec une taille de %d\n", it_occupe->adresse, it_occupe->taille);
   it_occupe = it_occupe->suivant;
   }
   }

   }
 */

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

int choisi_allocation(){
    int i = rand()%500;
    i = (i/10)*10;

    return i;
}
