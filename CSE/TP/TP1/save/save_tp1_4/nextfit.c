#include "nextfit.h"
#include "allocation.h"

liste g_nf_it_libre = NULL; //fleche pour l'algorithme nextfit

//fonction permettant d'initialiser une liste libre et une liste occupée selon l'aglo nextfit
int initialiser_nf(liste *l_libre, liste *l_occupe){
    *l_libre = allocation(1, sizeof(cell));

    (*l_libre)->adresse = 0;
    (*l_libre)->taille = 2000;
    (*l_libre)->suivant = *l_libre;
    (*l_libre)->precedent = *l_libre;

    g_nf_it_libre = *l_libre; //on fait pointer la flêche sur la première case de la liste

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

            if(prec->suivant == prec) // si il n'y avait que 3 blocs, on les a fusionné donc il faut refaire pointer precedent sur lui-même
                prec->precedent = prec;

            free(suiv);
            free(act);

            g_nf_it_libre = prec->suivant; //on maj notre flêche
        }
        else{
            if(prec->taille == act->adresse - prec->adresse){ //fusion de l'actuel et du precedent
                prec->taille = prec->taille + act->taille;
                prec->suivant = act->suivant;
                (prec->suivant)->precedent = prec;
                
                if(prec->suivant == prec) //si il n'y a plus qu'un noeud on met a jour le precedent que l'on fait pointer sur lui-même
                    prec->precedent = prec;
                
                free(act);
                
                g_nf_it_libre = prec->suivant; //on maj notre flêche
            }
            else if(act->taille == suiv->adresse - act->adresse){ //fusion de l'actuel et du suivant
                act->taille = act->taille + suiv->taille;
                act->suivant = suiv->suivant;
                (act->suivant)->precedent = act;

                if(act->suivant == act)
                    act->precedent = act;

                free(suiv);
                
                g_nf_it_libre = act->suivant; //on maj notre flêche
            }
        }
    }
}


//fonction permettant d'insérer un processus dans la liste occupée selon une taille et une adresse données. Retourne 1 en cas de succès, 0 sinon
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
        //sinon on parcourt notre liste tant qu'on est pas arrivé à la fin et que l'adresse est inférieure
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


//fonction permettant d'ajouter une zone libre dans la liste libre donnée selon une adresse et une taille donnée
liste liberer_nf(int a, int t, liste *l_libre){
    liste it_libre = *l_libre;
    liste noeud = NULL;
    liste fin = NULL;

    //si la liste libre est vide alors on créé simplement un noeud, on fait pointer le suivant et le precedent sur lui-même puis on le retourne
    if(it_libre == NULL){
        *l_libre = creer_noeud(a, t, NULL, NULL);
        (*l_libre)->precedent = *l_libre;
        (*l_libre)->suivant = *l_libre;

        g_nf_it_libre = *l_libre; //on maj notre flêche

        return *l_libre;
    }
    //sinon si la première cellule a déjà une adresse supérieure à celle qu'on veut mettre, on créé un zone libre au tout début de la liste
    else if(it_libre->adresse >= a){
        //on créé un noeud et on met à jour les suivant et les precedent, puis on modifie la liste libre de telle sorte qu'elle pointe sur notre nouveau noeud
        noeud = creer_noeud(a, t, NULL, NULL);
        noeud->precedent = it_libre->precedent;
        noeud->suivant = it_libre;
        it_libre->precedent = noeud;
        (noeud->precedent)->suivant = noeud;

        *l_libre = noeud;

        //on fusionne éventuellement les zones libres adjacents
        fusion_nf((*l_libre)->precedent, *l_libre, (*l_libre)->suivant);

        return *l_libre;
    }
    else{
        //on construit un pointeur qui nous permettra d'arrêter notre boucle
        fin = it_libre;

        //on se déplace pour trouver l'endroit ou il faut mettre notre zone
        while(it_libre->suivant != fin && (it_libre->suivant)->adresse < a){
            it_libre = it_libre->suivant;
        }

        //si le suivant est la fin, alors on ajoute un noeud à la fin de notre liste circulaire
        if(it_libre->suivant == fin){ 
            noeud = creer_noeud(a, t, NULL, NULL); 
            noeud->suivant = fin;
            noeud->precedent = it_libre;
            it_libre->suivant = noeud;
            fin->precedent = noeud;

            fusion_nf(it_libre, noeud, fin);

            return noeud;
        }
        else{
            //sinon on insere une zone libre entre deux noeuds et on fusionne éventuellement les zones libres adjacents
            noeud = creer_noeud(a, t, NULL, NULL); 
            noeud->suivant = it_libre->suivant;
            noeud->precedent = it_libre;
            it_libre->suivant = noeud;
            (noeud->suivant)->precedent = noeud;

            fusion_nf(it_libre, noeud, noeud->suivant);

            return noeud;
        }
    }

}


//fonction permettant de compacter une liste occupée donnée selon une liste libre et une taille.
int compacter_nf(int t, liste *l_occupe, liste *l_libre){
    liste it_occupe = *l_occupe;
    liste it_libre = *l_libre;
    liste fin = it_libre;
    int taille = 0;

    //on place notre première zone occupée à l'adresse 0
    it_occupe->adresse = 0;
    taille += it_occupe->taille;

    //puis on compacte toute la liste occupée
    while(it_occupe->suivant != NULL){
        (it_occupe->suivant)->adresse = taille;
        taille += (it_occupe->suivant)->taille;
        it_occupe = it_occupe->suivant;
    }

    //on supprime tous les blocs libres sauf le premier
    while(it_libre->suivant != fin){
        free(it_libre->suivant);
        it_libre = it_libre->suivant;
    }

    //que l'on met à jour en modifiant sa taille, son adresse et comme il n'y aura que ce noeud dans la liste libre on fait pointer les suivants et precedents sur lui-même
    (*l_libre)->adresse = it_occupe->adresse + it_occupe->taille;
    (*l_libre)->taille = 2000 - (*l_libre)->adresse;
    (*l_libre)->precedent = *l_libre;
    (*l_libre)->suivant = *l_libre;

    g_nf_it_libre = *l_libre; //on maj notre flêche


    //puis on rappelle la fonction allouer en espérant que cette fois ci il y aura assez de place pour allouer le processus de taille voulue
    printf("Compactage...\n\n");
    return allouer_nf(t, &(*l_libre), l_occupe, 0);
}


//fonction permettant de supprimer un cellule occupée selon une liste occupée, une taille et une liste libre
int supprime_occupe_nf(int t, liste *l_occupe, liste *l_libre){
    liste it_occupe = *l_occupe;
    liste it_occupe2;
    liste it_libre;

    //si la liste est vide il n'y a rien a supprimer on retourne 0
    if(it_occupe == NULL){
        return 0;
    }
    //sinon si la première cellule est la bonne
    else if(it_occupe->taille == t){
        //on créé une zone libre
        it_libre = liberer_nf(it_occupe->adresse, it_occupe->taille, l_libre);
        //on supprime le premier noeud
        *l_occupe = it_occupe->suivant;
        (*l_occupe)->precedent = NULL;
        free(it_occupe);

        return 1;
    }
    else{
        //sinon on  cherche l'adresse tant qu'on est pas arrivé jusqu'à la fin
        while(it_occupe->suivant != NULL && (it_occupe->suivant)->taille != t){
            it_occupe = it_occupe->suivant;
        }

        //si it_occupe->suivant == NULL, alors on est arrivé à la fin donc on a pas trouvé le bloc désiré, on retourne 0
        if(it_occupe->suivant == NULL){
            return 0;
        }
        else{ // sinon on a trouvé la bonne zone

            //on créé alors une zone libre dans la liste libre selon l'adresse et la taille trouvée
            it_libre = liberer_nf((it_occupe->suivant)->adresse, (it_occupe->suivant)->taille, l_libre);

            //et on supprime le processus
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

            return 1;
        }
    }
}


//fonction permettant d'allouer un processus de taille t selon une liste libre, une liste occupée et selon un booléen de compactage
int allouer_nf(int t, liste *l_libre, liste *l_occupe, int c){
    liste it_libre2;
    liste save_it_libre;
    liste fin;

    //si la flêche n'a pas de valeur on la met à jour en la mettant sur la première zone libre de la liste libre
    if(g_nf_it_libre == NULL)
        g_nf_it_libre = *l_libre;

    save_it_libre = g_nf_it_libre; //on prend une sauvegarde de la fleche à l'état initial

    fprintf(stderr, "la fleche vaut %d et la sauvegarde vaut %d\n", g_nf_it_libre->adresse, save_it_libre->adresse);
    
    if(g_nf_it_libre == NULL){ // si on a pas de liste libre alors on retourne 0 car on ne peut rien allouer
        return 0;
    }
    else if(g_nf_it_libre->taille >= t){ //si le premier convient, on insere un processus occupé à l'adresse voulue
    
    
    insere_occupe_nf(g_nf_it_libre->adresse, t, l_occupe);

        //on met à jour la zone libre
        g_nf_it_libre->adresse = g_nf_it_libre->adresse + t;
        g_nf_it_libre->taille = g_nf_it_libre->taille - t;
    
        //fprintf(stderr, "on est là ou je pense et adresse de la zone libre vaut %d et la taile %d \n", g_nf_it_libre->adresse, g_nf_it_libre->taille);

        if(g_nf_it_libre->adresse <= g_nf_it_libre->precedent->adresse) //alors il faut mettre à jour la liste pour qu'elle pointe sur notre nouveau bloc
            *l_libre = g_nf_it_libre;

        //si la zone libre contient une taille nulle alors on la supprime
        if(g_nf_it_libre->taille == 0){
            if((g_nf_it_libre->precedent)->adresse > g_nf_it_libre->adresse){ // alors c'était le premier de la liste circulaire, il faut maj *l_libre
                it_libre2 = *l_libre;

                (g_nf_it_libre->precedent)->suivant = g_nf_it_libre->suivant;
                (g_nf_it_libre->suivant)->precedent = g_nf_it_libre->precedent;
                *l_libre = g_nf_it_libre->suivant;

                free(it_libre2);

                g_nf_it_libre = *l_libre; //on maj notre fleche
            }
            else if((g_nf_it_libre->precedent)->adresse == g_nf_it_libre->adresse){ // alors la liste libre contenait qu'un singleton, il faut mettre à jour *l_libre à NULL car elle ne contiendra plus de zone libre
                free(*l_libre);
                *l_libre = NULL;
                g_nf_it_libre = NULL; //notre fleche ne pointe plus sur rien
            }
            else{ //sinon c'est un noeud normal que l'on supprime
                it_libre2 = g_nf_it_libre;

                (g_nf_it_libre->precedent)->suivant = g_nf_it_libre->suivant;
                (g_nf_it_libre->suivant)->precedent = g_nf_it_libre->precedent;

                g_nf_it_libre = g_nf_it_libre->suivant; //on met à jour notre fleche

                free(it_libre2);
            }
        }
        return 1;
    }
    else{
        //sinon alors on crée notre future condition d'arrêt afin de chercher une zone libre qui assez grande
        fin = g_nf_it_libre;

        // on se déplace jusqu'à trouver une zone libre qui convient
        while(g_nf_it_libre->suivant != fin && (g_nf_it_libre->suivant)->taille < t){
            g_nf_it_libre = g_nf_it_libre->suivant;
        }

        //on a pas trouvé de zone assez grande
        if(g_nf_it_libre->suivant == fin){
            //si le compactage est activé on compacte
            if(c == 1){
                return compacter_nf(t, l_occupe, l_libre);
            }
            //sinon on remet notre fleche à son état initial, avant le parcourt et on retourne 0
            else{
                g_nf_it_libre = save_it_libre;
                return 0;
            }
        }
        else{
            //sinon alors on insere un occupée à l'adresse trouvée et selon la taille donnée
            insere_occupe_nf((g_nf_it_libre->suivant)->adresse, t, l_occupe);

            //on met à jour la zone libre
            (g_nf_it_libre->suivant)->adresse = (g_nf_it_libre->suivant)->adresse + t;
            (g_nf_it_libre->suivant)->taille = (g_nf_it_libre->suivant)->taille - t;

            if(g_nf_it_libre->adresse <= g_nf_it_libre->precedent->adresse) //alors il faut mettre à jour la liste pour qu'elle pointe sur notre nouveau bloc
                *l_libre = g_nf_it_libre;
            
            g_nf_it_libre = g_nf_it_libre->suivant; // on met notre fleche sur le noeud qui nous interresse

            if(g_nf_it_libre->taille == 0){
                if((g_nf_it_libre->precedent)->adresse > g_nf_it_libre->adresse){ // alors c'était le premier de la liste circulaire, il faut maj *l_libre
                    it_libre2 = *l_libre;

                    (g_nf_it_libre->precedent)->suivant = g_nf_it_libre->suivant;
                    (g_nf_it_libre->suivant)->precedent = g_nf_it_libre->precedent;
                    *l_libre = g_nf_it_libre->suivant;

                    g_nf_it_libre = g_nf_it_libre->suivant; //on maj notre fleche
                    
                    free(it_libre2);

                }
                else if((g_nf_it_libre->precedent)->adresse == g_nf_it_libre->adresse){ 
                    free(*l_libre);
                    *l_libre = NULL;
                    g_nf_it_libre = NULL; //notre fleche ne pointe plus sur rien
                }
                else{ //sinon c'est un noeud normal que l'on supprime
                    it_libre2 = g_nf_it_libre;

                    (g_nf_it_libre->precedent)->suivant = g_nf_it_libre->suivant;
                    (g_nf_it_libre->suivant)->precedent = g_nf_it_libre->precedent;

                    g_nf_it_libre = g_nf_it_libre->suivant; //on met à jour notre fleche

                    free(it_libre2);
                }

            }

            return 1;
        }
    }
}


//fonction permettant d'afficher les listes occupée et libre en nextfit
void afficher_nf(liste l_libre, liste l_occupe){
    liste it_libre = l_libre;
    liste it_occupe = l_occupe;
    liste fin = it_libre;
    
    printf("\n");

    if(l_libre){
        do{
            //printf("---precedent : %d (libre -> %d %d %d) suivant : %d---", it_libre->precedent->adresse, it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille), it_libre->suivant->adresse);
            printf("---%d(libre -> %d %d %d)%d---", it_libre->precedent->adresse, it_libre->adresse, it_libre->taille, (it_libre->adresse+it_libre->taille), it_libre->suivant->adresse);
            
            it_libre = it_libre->suivant;
        }while(it_libre != fin);
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




