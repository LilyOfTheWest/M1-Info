#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
     // Tableau des 3 meilleurs scores

    fichier = fopen("test.txt", "r");
    int score[3] = {0};
    int lu;
    char s[1000];
    if (fichier != NULL)
    {
        lu=fscanf(fichier, "%s",s);
        printf("%s\nOn a lu : %d", s, lu);

        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier text.txt");
    }
    return 0;
}
