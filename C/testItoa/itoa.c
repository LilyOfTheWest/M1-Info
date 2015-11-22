#include <stdio.h>
#include <stdlib.h>

char *my_itoa(int n)
{
  char *s = NULL;
  int i = 0, m = 0, k = 0, taille = 0;
  int n2 = n;
  do
  {
    n2 = n2/10;
    taille++;
  }while(n2 !=0 );
  if(n < 0)
    {
      k = n;
      n = -n;
      taille = taille + 2;
    }
  else taille = taille + 1;
  s = malloc((taille)*sizeof(char));
  if (s == NULL)
    exit(EXIT_FAILURE);
  i = taille-1;
  s[taille-1] = '\0';
  while(n!=0)
  {
    m = n%10;
    n = n/10;
    s[i-1] = m +'0';
    i--;
  }

  if(k < 0)
  {
    s[0] = '-';
  }
  return s;
}
