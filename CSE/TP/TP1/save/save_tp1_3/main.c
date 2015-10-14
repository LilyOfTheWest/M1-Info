#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "lirecar.h"
#include "firstfit.h"
#include "nextfit.h"
#include "fonction_generale.h"

int main(int argc, char* argv[], char *envp[]){
    char reponse;
    int allocation, desallocation, compactage;
    /* Autres déclarations                                */

    /* Récupération des arguments de la ligne de commande */
    if(argc == 2){
        if(strcmp(argv[1], "-c") == 0)
            compactage = 1;
        else
            fprintf(stderr, "Erreur, paramètre %s inconnu \n", argv[1]);
    }
    else
        compactage = 0;

    /* Initialisations                                    */
    liste ll_ff = NULL;
    liste lo_ff = NULL;
    initialiser_ff(&ll_ff, &lo_ff);

    liste ll_nf = NULL;
    liste lo_nf = NULL;
    initialiser_nf(&ll_nf, &lo_nf);

    liste ll_bf = NULL;
    liste lo_bf = NULL;
    initialiser_nf(&ll_bf, &lo_bf);

    srand(time(NULL));


    /* Boucle */
    do {
        /* Détermination d'une suite aléatoire
           d'allocations/désallocations de mémoire       */

        allocation = choisi_allocation();
        desallocation = choisi_desallocation(lo_ff);



        /* Simulation et affichage avec First Fit       */
        
        printf("\n\n\n############# Firstfit ########### \n\n");
        
        if(allouer_ff(allocation, &ll_ff, &lo_ff, compactage) == 1){
            printf("\n\nAllocation firstfit de %dMo bien effectuée. \n\n", allocation);
        }
        else{
            fprintf(stderr, "\n\nErreur, impossible d'allouer %dMo en firstfit. \n\n", allocation);
        }

        afficher_ff(ll_ff, lo_ff);

        if(desallocation != 0){
            if(supprime_occupe_ff(desallocation, &lo_ff, &ll_ff) == 1){
                printf("\n\nDésallocation firstfit de la taille %d bien effectuée. \n\n", desallocation);
            }
            else{
                fprintf(stderr, "\n\nErreur, impossible de désallouer la taille %d.\n\n", desallocation);
            }

            afficher_ff(ll_ff, lo_ff);
        }
        else{
            printf("\n\nPas de désallocation pour ce tour ! \n\n");
        }


        /* Simulation et affichage avec Next Fit       */

        printf("\n\n\n############# Nextfit ########### \n\n");
        
        if(allouer_nf(allocation, &ll_nf, &lo_nf, compactage) == 1){
            printf("\n\nAllocation nextfit de %dMo bien effectuée. \n\n", allocation);
        }
        else{
            fprintf(stderr, "\n\nErreur, impossible d'allouer %dMo en nextfit. \n\n", allocation);
        }

        afficher_nf(ll_nf, lo_nf);

        if(desallocation != 0){
            if(supprime_occupe_nf(desallocation, &lo_nf, &ll_nf) == 1){
                printf("\n\nDésallocation nextfit de la taille %d bien effectuée. \n\n", desallocation);
            }
            else{
                fprintf(stderr, "\n\nErreur, impossible de désallouer la taille %d en nextfit.\n\n", desallocation);
            }

            afficher_nf(ll_nf, lo_nf);
        }
        else{
            printf("\n\nPas de désallocation pour ce tour ! \n\n");
        }



        /* Simulation et affichage avec Best Fit       */
        
        /*
        printf("\n\n\n############# Bestfit ########### \n\n");
        
        if(allouer_bf(allocation, &ll_bf, &lo_bf, compactage) == 1){
            printf("\n\nAllocation bestfit de %dMo bien effectuée. \n\n", allocation);
        }
        else{
            fprintf(stderr, "\n\nErreur, impossible d'allouer %dMo en nextfit. \n\n", allocation);
        }

        afficher_ff(ll_bf, lo_bf);

        if(desallocation != 0){
            if(supprime_occupe_nf(desallocation, &lo_bf, &ll_bf) == 1){
                printf("\n\nDésallocation bestfit de la taille %d bien effectuée. \n\n", desallocation);
            }
            else{
                fprintf(stderr, "\n\nErreur, impossible de désallouer la taille %d.\n\n", desallocation);
            }

            afficher_ff(ll_bf, lo_bf);
        }
        else{
            printf("\n\nPas de désallocation pour ce tour ! \n\n");
        }
        */


        lirecar("Encore (o/n)? ", &reponse);

    } while ((reponse == 'o') || (reponse == 'O'));

    detruire_liste(&ll_ff);
    detruire_liste(&lo_ff);
    detruire_liste(&ll_nf);
    detruire_liste(&lo_nf);
    detruire_liste(&ll_bf);
    detruire_liste(&lo_bf);


    /* C'est fini                                         */
    exit(0);
}
