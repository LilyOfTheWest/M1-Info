TP réalisé par Line POUVARET & Mickaël TURNEL

Tout le TP a été fait.

Compilation:
	"make" : compile les programmes de test avec une librairie statique par défaut

	Pour compiler avec une librairie dynamique, il faut:
		- ouvrir le Makefile
		- décommenter la ligne avec LDFLAGS de la compilation avec la librairie voulu
		- remplacer "static" par "dynamic" dans la règle "all"

Programmes de test:
	"./test <fichier 1> <fichier 2>" : copie le contenu du fichier 1 dans le fichier 2
	"./genere_notes <nb> <fichier>" : génère nb note aléatoire sous la forme "note= 2, coef= 3" dans le fichier
	"./moyenne <fichier>" : lit les notes du fichier générer par la commande précédente et fait la moyenne

	"make tests" va lancer les commandes suivantes:
		./test test.txt resultat.txt
		./genere_notes 10 notes.txt
		./moyenne notes.txt

Problèmes:
	Il y a un bug que je n'ai pas réussi à corriger avec fliref.
	Le programme moyenne ne peut pas lire plus de 12 notes.