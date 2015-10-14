#include "bestfit.h"
#include "allocation.h"


//fonction permettant d'initialiser une liste libre et une liste occupee selon l'algo firstfit
int initialiser_bf(liste *l_libre, liste *l_occupe){
    *l_libre = allocation(1, sizeof(cell));

    (*l_libre)->adresse = 0;
    (*l_libre)->taille = 2000;
    (*l_libre)->suivant = NULL;
    (*l_libre)->precedent = NULL;

    //la liste occupee est vide au tout début, donc pointeur null
    *l_occupe = NULL;

    return 1;
}

void fusion_bf_prec(liste *l_libre, liste act, liste prec){
    liste it = *l_libre;
    liste it2 = NULL;
    fprintf(stderr, "on étudie l'adresse %d, et l'actuel est %d\n", it->adresse, act->adresse);
    //traitement du cas de la première zone libre de la liste
    if((it->adresse + it->taille) == act->adresse){ //fusion de l'actuel et du precedent
        act->taille = act->taille + it->taille;
        act->adresse = it->adresse;


        fprintf(stderr, "notre nouveau bloc fait %d de taille et à l'adresse %d\n", act->taille, act->adresse);
        afficher_bf(*l_libre, NULL);

        if(it == prec)
            prec = NULL;

        *l_libre = it->suivant; //on supprime it car on l'a fusionné
        if(prec)
            prec->suivant = act->suivant; //on enlève le bloc act qu'on a fusionné
        else
            *l_libre = act->suivant;


        afficher_bf(*l_libre, NULL);


        prec = inserer_libre_trie(l_libre, act); //on insere act dans la liste libre afin qu'elle reste triée, car on a augmenté sa taille

        afficher_bf(*l_libre, NULL);

        fprintf(stderr, "1\n");

        return fusion_bf_suiv(l_libre, act, prec);
    }
    else{
        while(it && it->suivant){
            fprintf(stderr, "on étudie l'adresse %d et l'actuel est %d\n", it->suivant->adresse, act->adresse);
            if(((it->suivant)->adresse + (it->suivant)->taille) == act->adresse){ //fusion de l'actuel et du precedent
                act->taille = act->taille + (it->suivant)->taille; // on augmente la taille de la zone precedente
                act->adresse = (it->suivant)->adresse;

                fprintf(stderr, "notre nouveau bloc fait %d de taille et à l'adresse %d\n", act->taille, act->adresse);

                afficher_bf(*l_libre, NULL);


                if(it->suivant == prec)
                    prec = it;

                it->suivant = (it->suivant)->suivant; //on supprime it->suivant qu'on a fusionné


                if(prec)
                    prec->suivant = act->suivant; //on enlève le bloc act qu'on a fusionné
                else
                    *l_libre = act->suivant;


                afficher_bf(*l_libre, NULL);

                prec = inserer_libre_trie(l_libre, act); //on insere act dans la liste libre afin qu'elle reste triée, car on a augmenté sa taille

                afficher_bf(*l_libre, NULL);

                fprintf(stderr, "3\n");

                return fusion_bf_suiv(l_libre, act, prec);
            }

            it = it->suivant;
        }
    }
}



void fusion_bf_suiv(liste *l_libre, liste act, liste prec){
    liste it = *l_libre;
    liste it2 = NULL;
    if(prec)
    fprintf(stderr, "on étudie l'adresse %d et l'actuel est %d et prec est %d\n", it->adresse, act->adresse, prec->adresse);
    else
    fprintf(stderr, "on étudie l'adresse %d et l'actuel est %d et prec est null\n", it->adresse, act->adresse);
    if(it->adresse == (act->adresse + act->taille)){ //fusion de l'actuel et du suivant
        act->taille = act->taille + it->taille;

        fprintf(stderr, "notre nouveau bloc fait %d de taille et à l'adresse %d\n", act->taille, act->adresse);
        afficher_bf(*l_libre, NULL);

        it2 = it; //on sauvegarde it pour le liberer après

        if(it == prec)
            prec = NULL;
        
        *l_libre = it->suivant; 
        
        if(prec)
            prec->suivant = act->suivant; //on enlève le bloc act qu'on a fusionné
        else
            *l_libre = act->suivant;




        afficher_bf(*l_libre, NULL);


        inserer_libre_trie(l_libre, act); //on insere act dans la liste libre afin qu'elle reste triée, car on a augmenté sa taille

        afficher_bf(*l_libre, NULL);

        fprintf(stderr, "2\n");

        return;
    }

    while(it && it->suivant){
if(prec)
    fprintf(stderr, "on étudie l'adresse %d et l'actuel est %d et prec est %d\n", it->adresse, act->adresse, prec->adresse);
    else
    fprintf(stderr, "on étudie l'adresse %d et l'actuel est %d et prec est null\n", it->adresse, act->adresse);

        if((it->suivant)->adresse == (act->adresse + act->taille)){ //fusion de l'actuel et du suivant
            act->taille = act->taille + (it->suivant)->taille;

            fprintf(stderr, "notre nouveau bloc fait %d de taille et à l'adresse %d\n", act->taille, act->adresse);

            afficher_bf(*l_libre, NULL);
            it2 = it->suivant;

            if(it->suivant == prec)
                prec = it;

            it->suivant = (it->suivant)->suivant;

            if(prec)
                prec->suivant = act->suivant; //on enlève le bloc act qu'on a fusionné
            else
                *l_libre = act->suivant;

            afficher_bf(*l_libre, NULL);

            inserer_libre_trie(l_libre, act); //on insere act dans la liste libre afin qu'elle reste triée, car on a augmenté sa taille
            afficher_bf(*l_libre, NULL);

            fprintf(stderr, "4\n");
            return;
        } 
        it = it->suivant;
    }
}


//fonction permettant de fusionner les listes libres si elles sont adjacentes
void fusion_bf(liste *l_libre, liste act, liste prec){
    fprintf(stderr, "fusion du precedent avec l'actuel ?\n");
    fusion_bf_prec(l_libre, act, prec);

    fprintf(stderr, "fusion du suivant avec l'actuel ?\n");
    fusion_bf_suiv(l_libre, act, prec);
}


liste inserer_libre_trie(liste *l_libre, liste act){
    liste it = *l_libre;

    if(it == NULL){
        *l_libre = act;
        return NULL;
    }
    else if(it->taille >= act->taille){
        act->suivant = *l_libre;
        *l_libre = act;
        return NULL;
    }
    else{
        while(it->suivant && (it->suivant)->taille < act->taille)
            it = it->suivant;

        if(it->suivant == NULL){ //dernier de la liste
            it->suivant = act;
            act->suivant = NULL;
            return it;
        }
        else{
            act->suivant = it->suivant;
            it->suivant = act;
            return it;
        }
    }
}


//fonction permettant d'insérer un processus dans la liste occupée donnée selon une taille et une adresse. Retourne 1 en cas de succès, 0 sinon
int insere_occupe_bf(int a, int t, liste *l_occupe){
    liste it_occupe = *l_occupe;

    //si la liste est vide alors on créé simplement un noeud sans suivant
    if(it_occupe == NULL){
        *l_occupe = creer_noeud(a, t, NULL, NULL);
        return 1;
    }
    //si la premiere cellule de la liste a déjà une adresse supérieure à celle qu'on veut mettre, alors on crée un noeud au tout début de la liste
    else if(it_occupe->adresse >= a){
        *l_occupe = creer_noeud(a, t, NULL, it_occupe);
        return 1;
    }
    else{
        //sinon on parcourt notre liste tant qu'on est pas arrivé à la fin et que l'adresse est inférieure
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


//fonction permettant d'ajouter une zone libre dans une liste libre donnée selon une adresse et une taille. Retourne la zone libre crée
liste liberer_bf(int a, int t, liste *l_libre){
    liste it_libre = *l_libre;
    liste it_libre2 = NULL;

    //si la liste libre est vide alors on créé simplement un noeud
    if(it_libre == NULL){
        *l_libre = creer_noeud(a, t, NULL, NULL);
        return *l_libre;
    }
    //sinon si la première cellule a déjà une adresse supérieure à celle qu'on veut mettre, on créé un zone libre au tout début de la liste
    else if(it_libre->taille >= t){
        *l_libre = creer_noeud(a, t, NULL, it_libre); 

        //on fusionne éventuellement les zones libres adjacentes
        fusion_bf(l_libre, *l_libre, NULL);

        return *l_libre;
    }
    else{
        //on se déplace pour trouver l'endroit ou il faut mettre notre zone
        while(it_libre->suivant != NULL && (it_libre->suivant)->taille < t){
            it_libre = it_libre->suivant;
        }

        //si le suivant est null on est à la fin de la liste donc on rajoute simplement un noeud à la fin de la liste libre et on fusionne les zone libres adjacentes
        if(it_libre->suivant == NULL){ 
            it_libre->suivant = creer_noeud(a, t, NULL, NULL); 

            fusion_bf(l_libre, it_libre->suivant, it_libre);

            return it_libre->suivant;
        }
        else{
            //sinon on insere une zone libre entre deux noeuds et on fusionne éventuellement les zones libres adjacentes
            it_libre2 = it_libre->suivant;
            it_libre->suivant = creer_noeud(a, t, NULL, it_libre2); 

            fusion_bf(l_libre, it_libre->suivant, it_libre);

            return it_libre->suivant;
        }
    }

}


//fonction permettant de compacter une liste occupée donnée, une liste libre et selon la taille du bloc à allouer. 
int compacter_bf(int t, liste *l_occupe, liste *l_libre){
    liste it_occupe = *l_occupe;
    liste it_libre = *l_libre;
    int taille = 0;

    //on compacte l'adresse du premier occupé : on le place tout au début de la liste
    it_occupe->adresse = 0;
    taille += it_occupe->taille;

    //on compacte tous les suivants de la la liste occupée
    while(it_occupe->suivant != NULL){
        (it_occupe->suivant)->adresse = taille;
        taille += (it_occupe->suivant)->taille;
        it_occupe = it_occupe->suivant;
    }

    //on supprime tous les blocs libres sauf le premier
    while(it_libre->suivant){
        free(it_libre->suivant);
        it_libre = it_libre->suivant;
    }

    //que l'on modifie afin qu'il retrouve une taille normale, à une adresse de sorte qu'il soit tout à la fin des blocs occupés
    (*l_libre)->suivant = NULL;
    (*l_libre)->precedent = NULL;
    (*l_libre)->adresse = it_occupe->adresse + it_occupe->taille;
    (*l_libre)->taille = 2000 - (*l_libre)->adresse;

    //on abfiche un message puis on réappelle la fonction allouer
    printf("Compactage...\n\n");
    return allouer_bf(t, &(*l_libre), l_occupe, 0);
}


//fonction permettant de supprimer un cellule occupée selon une liste occupée, une taille et une liste libre. Retourne 1 en cas de succès, 0 sinon
int supprime_occupe_bf(int t, liste *l_occupe, liste *l_libre){
    liste it_occupe = *l_occupe;
    liste it_occupe2;
    liste it_libre;

    //si la liste est vide il n'y a rien a supprimer on retourne 0
    if(it_occupe == NULL){
        return 0;
    }
    //sinon si la première cellule est la bonne
    else if(it_occupe->taille == t){
        //on ajoute une zone libre dans la liste libre
        it_libre = liberer_bf(it_occupe->adresse, it_occupe->taille, l_libre);
        //on supprime le premier noeud
        *l_occupe = it_occupe->suivant;
        free(it_occupe);

        return 1;
    }
    else{
        //on  cherche la taille voulue tant qu'on est pas arrivé jusqu'à la fin
        while(it_occupe->suivant != NULL && (it_occupe->suivant)->taille != t){
            it_occupe = it_occupe->suivant;
        }

        if(it_occupe->suivant == NULL){ // on a pas trouvé le programme avec la taille spécifiée, on retourne 0
            return 0;
        }
        else{
            //sinon on crée une zone libre dans la liste libre
            it_libre = liberer_bf((it_occupe->suivant)->adresse, (it_occupe->suivant)->taille, l_libre);

            //puis on supprime le processus de la liste occupée
            it_occupe2 = it_occupe->suivant;
            it_occupe->suivant = (it_occupe->suivant)->suivant;
            free(it_occupe2);

            return 1;
        }
    }
}


//fonction permettant d'allouer un processus selon une taille donnée, une liste libre, une liste occupée et un booléen de compactage. Retourne 1 en cas de succès, 0 sinon.
int allouer_bf(int t, liste *l_libre, liste *l_occupe, int c){
    liste it_libre = *l_libre;
    liste it_libre2;

    //si il n'y a pas de liste libre on ne peut rien allouer donc on retourne 0
    if(it_libre == NULL){ 
        return 0;
    }
    else if(it_libre->taille >= t){ // si la première cellule de la liste convient alors on la prend
        //on insère dans la liste occupée le processus selon l'adresse trouvée
        insere_occupe_bf(it_libre->adresse, t, l_occupe);

        //on soustrait à la zone libre la taille allouée et on change son adresse
        it_libre->adresse = it_libre->adresse + t;
        it_libre->taille = it_libre->taille - t;

        //si la taille est devenu nulle on supprime la zone libre
        if(it_libre->taille == 0){
            *l_libre = (*l_libre)->suivant;
            free(it_libre);
        }
        //pas besoin de réinserer le noeud, vu qu'on le diminue et qu'il était déjà le plus petit de la liste il reste le plus petit

        return 1;
    }
    else{
        // on se déplace jusqu'à trouver une zone libre qui convient
        while(it_libre->suivant != NULL && (it_libre->suivant)->taille < t){
            it_libre = it_libre->suivant;
        }

        //si le suivant est nul on a pas trouvé de zone libre subfisement grande
        if(it_libre->suivant == NULL){
            //si compactage est activé, on appelle la fonction compacter
            if(c == 1){
                return compacter_bf(t, l_occupe, l_libre);
            }
            //sinon on ne peut rien allouer donc on retourne 0
            else{
                return 0;
            }
        }
        else{ // on a trouvé la bonne zone donc on insere le processus dans la liste occupée
            insere_occupe_bf((it_libre->suivant)->adresse, t, l_occupe);

            //on met à jour la zone libre
            (it_libre->suivant)->adresse = (it_libre->suivant)->adresse + t;
            (it_libre->suivant)->taille = (it_libre->suivant)->taille - t;

            //si la zone libre contient une taille nulle alors on la supprime
            if((it_libre->suivant)->taille == 0){
                it_libre2 = it_libre->suivant;
                it_libre->suivant = (it_libre->suivant)->suivant;
                free(it_libre2);
            }
            else{
                it_libre2 = it_libre->suivant; //on sauvegarde notre noeud
                it_libre->suivant = (it_libre->suivant)->suivant; //on enleve le noeud de la liste libre
                inserer_libre_trie(l_libre, it_libre2); //pour le réinserer à la bonne place
            }


            return 1;
        }
    }
}


//fonction permettant d'abficher les listes occupée et libre en firstfit
void afficher_bf(liste l_libre, liste l_occupe){
    liste it_libre = l_libre;
    liste it_occupe = l_occupe;

    printf("\n");

    if(l_libre){
        while(it_libre){
            if(it_libre->suivant)
                printf("---(libre -> %d %d %d)%d---",  it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille), it_libre->suivant->adresse);
            else
                printf("---(libre -> %d %d %d)NULL---",  it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille));
            it_libre = it_libre->suivant;
        }
    }
    else{
        printf("Pas de libre :(\n");
    }   

    printf("\n\n");

    if(l_occupe){
        while(it_occupe){
            printf("---(occupe -> %d %d %d)---", it_occupe->adresse, it_occupe->taille, (it_occupe->adresse+it_occupe->taille));
            it_occupe = it_occupe->suivant;
        }
    }
    else{
        printf("Pas d'occupés \n");
    }

    printf("\n");
}

