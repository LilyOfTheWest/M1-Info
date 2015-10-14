#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "lirecar.h"
#include "firstfit.h"
//#include "nextfit.h"
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
    initialiser(&ll_ff, &lo_ff);

    srand(time(NULL));


    /* Boucle */
    do {
        /* Détermination d'une suite aléatoire
           d'allocations/désallocations de mémoire       */

        allocation = choisi_allocation();
        desallocation = choisi_desallocation(lo_ff);



        /* Simulation et affichage avec First Fit       */
        if(allouer_ff(allocation, &ll_ff, &lo_ff) == 1){
            printf("\n\nAllocation firstfit de %dMo bien effectuée. \n\n", allocation);
        }
        else{
            fprintf(stderr, "\n\nErreur, impossible d'allouer %dMo en firstfit. \n\n", allocation);
        }

        afficher_ff(ll_ff, lo_ff);

        if(desallocation != 0){
            if(supprime_occupe_ff(desallocation, &lo_ff, &ll_ff, compactage) == 1){
                printf("\n\nDésallocation firstfit de l'adresse %d bien effectuée. \n\n", desallocation);
            }
            else{
                fprintf(stderr, "\n\nErreur, impossible de désallouer à l'adresse %d.\n\n", desallocation);
            }

            afficher_ff(ll_ff, lo_ff);
        }
        else{
            printf("\n\nPas de désallocation pour ce tour ! \n\n");
        }


        /* Simulation et affichage avec Next Fit       */

        /* Simulation et affichage avec Best Fit       */

        lirecar("Encore (o/n)? ", &reponse);

    } while ((reponse == 'o') || (reponse == 'O'));

    /* C'est fini                                         */
    exit(0);
}
