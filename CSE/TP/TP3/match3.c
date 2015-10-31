#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

struct chant_supporter {
  int nb_song;
  char* chant;
};

void *supporter (void *arg){
  struct chant_supporter *chant_sup = (struct chant_supporter *) arg ;
  int       i ;
  int       pid ;
  pthread_t tid ;  
  pid = getpid () ;
  tid = pthread_self () ;
  srand ((int) tid) ;

  for (i = 0; i < chant_sup->nb_song; i++){
    printf ("Processus %d Thread %x : %s \n", pid, (unsigned int) tid, chant_sup->chant) ;
    usleep (rand() / RAND_MAX * 1000000.) ;
  }
  return (void *) tid ;
}

int main (int argc, char **argv){

  int team1 ;
  int team2 ;
  int i ;
  int nb_threads = 0 ;
  pthread_t *tids ;
  struct chant_supporter *chant_team1, *chant_team2; 

  if (argc != 5){
    fprintf(stderr, "usage : %s team1 nb_chant1 team2 nb_chant2\n", argv[0]) ;
    exit (-1) ;
  }

  team1 = atoi (argv[1]) ;
  team2  = atoi (argv[3]) ;
  nb_threads = team1 + team2; 
  tids = malloc (nb_threads*sizeof(pthread_t)) ;

  chant_team1 = malloc (sizeof(struct chant_supporter));
  chant_team2 = malloc (sizeof(struct chant_supporter));

  chant_team1->nb_song = atoi (argv[2]);
  chant_team1->chant = "Allons enfants de la patrie...";
  chant_team2->nb_song = atoi (argv[4]);
  chant_team2->chant = "Sweep low, sweet chariot";

  /* Create the threads for team1 */
  for (i = 0 ; i < team1; i++){
    pthread_create (&tids[i], NULL, supporter, (void*)chant_team1) ;
  }
  /* Create the other threads (ie. team2) */
  for ( ; i < nb_threads; i++){
    pthread_create (&tids[i], NULL, supporter, (void*)chant_team2) ;
  }  

  /* Wait until every thread ened */ 
  for (i = 0; i < nb_threads; i++){
    pthread_join (tids[i], NULL) ;
  }
  
  free(chant_team1);
  free(chant_team2);

  free (tids) ;
  return EXIT_SUCCESS;
}
