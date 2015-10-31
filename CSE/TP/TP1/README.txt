TP1 CSE - Line Pouvaret, Mickaël Turnel

Exécution:
	./exoN <Nombre de processus> 
	où N est le numéro de l'exercice.

	Exemple: ./exo4 10

Makefile:
	make 			- Compile tous les exercices
	make clean 		- Supprime tous les fichiers .o
	make mrproper 	- Supprime les .o et les exécutables

Explications:
	Exercice 2-3:
		On se sert d'une structure Message qui sert à connaitre le rang, le pid et la valeur du processus qui a la plus grande valeur.

	Exercice 4:
		On créé notre segment de mémoire partagé d'une taille de n structure Processus (voir le fichier exo4.c). Chaque processus a sa propre zone et va écrire dans celle ci. Chaque processus est mis en attente tant que le processus précédent n'a pas renseigné sa valeur, une fois fait le processus actuel la compare à la sienne.
		Si sa valeur est plus grande, c'est ses propres informations qu'il va mettre dans sa "zone" sinon celles contenues dans la "zone" du processus précédent.
		Le processus père lui attend que le dernier processus ait fini puis affiche la valeur contenu dans sa "zone" qui contiendra les informations du processus ayant eu la plus grande valeur.