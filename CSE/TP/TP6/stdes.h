#ifndef _STDES_H
#define _STDES_H

struct _ES_FICHIER;
typedef struct _ES_FICHIER FICHIER;

FICHIER *ouvrir(char *nom, char mode);
int fermer(FICHIER*f);
int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f);
int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f);
int fliref(FICHIER *f, const char *format, ...)__attribute__((format(scanf, 2, 3)));
int fecriref(FICHIER *f, const char *format, ...)__attribute__((format(printf, 2, 3)));
char *conversion(int n);

#endif

