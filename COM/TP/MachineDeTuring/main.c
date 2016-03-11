#include <stdio.h>
#include <stdlib.h>
int ETAT;
void menu();
int sub(int x, int y);
void affiche_MT(char *MT, int taille);

int main(int argc, char**argv)
{
    int choix;

    int x, y, ok;
    ok = 1;

    do{
        menu();
        scanf("%d", &choix);
        switch(choix){
            case 1:
                printf("x = ?\n");
                scanf("%d", &x);
                printf("y = ?\n");
                scanf("%d", &y);
                int res = sub(x,y);
                if(res == -1){
                    printf("Erreur : x < y !\n");
                }
                else{
                        printf("%d - %d = %d\n\n", x, y, res);
                }
                break;
            default:
                ok = 0;
                break;
        }
    }while(ok==1);

    return 0;
}

void menu(){
    printf("MACHINE DE TURING\n");
    printf("1.  X-Y");
    printf("\n Votre choix ?\n");
}

int sub(int x, int y){
    int taille = x+2+y+3;
    int i;
    char MT[taille];
    for(i=0;i<taille;i++){
        if(i==0 || i==taille-1 || i==x+2)
            MT[i]='B';
        else{
            MT[i]='|';
        }
    }

    affiche_MT(MT, taille);
    i = 1;
    ETAT = 0;
    while(ETAT < 8){
        switch(ETAT){
        case 0:
            if(MT[i]=='|'){
                i++;
            }
            else if(MT[i] == 'B'){
                i++;
                ETAT=1;
            }
            break;
        case 1:
            if(MT[i]=='|'){
                i++;
            }
            else if(MT[i] == 'B' || MT[i] == '*'){
                ETAT=2;
                i--;
            }
            break;
        case 2:
            if(MT[i] == '|'){
                MT[i]='*';
                //affiche_MT(MT, taille);
            }
            else if(MT[i] == '*'){
                i--;
                ETAT = 3;
            }
            break;
        case 3:
            if(MT[i] == 'B'){
                i--;
                ETAT = 7; // qy0 = 7
            }
            else if(MT[i] == '|'){
                i--;
                ETAT = 4;
            }
            break;
        case 4:
            if(MT[i] == '|'){
                i--;
            }
            else if(MT[i] == 'B'){
                ETAT = 5;
                i--;
            }
            break;
        case 5:
            if(MT[i] == '|'){
                i--;
            }
            else if(MT[i] == 'B' || MT[i] == '*'){
                i++;
                ETAT = 6;
            }
            break;
        case 6:
            //printf("MT[%d] = %c\n", i, MT[i]);
            if(MT[i] == '|'){
                MT[i] = '*';
                //affiche_MT(MT, taille);
            }
            else if(MT[i] == '*'){
                i++;
                ETAT = 0;
            }
            else if(MT[i] == 'B'){
                ETAT = 9;
            }
            break;
        case 7:
            if(MT[i] == '|'){
                MT[i]='*';
                //affiche_MT(MT, taille);
                ETAT = 8; // qFin = 8
            }
            else if(MT[i] == '*'){
                ETAT = 9; // BOUCLE x < y
            }
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            break;
        }
        //printf("ETAT = %d\n",ETAT);
    }

    affiche_MT(MT, taille);
    if(ETAT == 8){
        int count = 0;
        for(i=0;i<taille;i++){
            if(MT[i] == '|')
                count++;
        }
        return count;
    }
    else if(ETAT == 9)
        return -1; // x < y
}


void affiche_MT(char *MT, int taille){
    int i = 0;
    printf("MT:\n[ ");
    for(i=0;i<taille;i++){
        printf("%c ", MT[i]);
    }
    printf("]\n\n");
}

