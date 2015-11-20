/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package batailleespagnole;

/**
 *
 * @author Lily
 */
public class BatailleEspagnole {

    public static void menu() {
        System.out.println("==========Menu Principal===========");
        System.out.println("-1- Nouvelle Partie");
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        menu();
        int choix = LectureClavier.lireEntier("Que voulez-vous faire ?");
        int nbJeuxMax, nbPtsMax, nbJoueurs, nbIA;
        switch (choix) {
            case 1:
                do {
                    nbJoueurs = LectureClavier.lireEntier("Combien de joueurs (2-4) au total?");
                } while (nbJoueurs < 2 || nbJoueurs > 4);

                do {
                    nbIA = LectureClavier.lireEntier("Combien de joueurs Ordinateur (0-4)?");
                } while (nbIA < 0 || nbIA > 4);
                do {
                    nbJeuxMax = LectureClavier.lireEntier("Entrez un nombre de jeux maximum (0=infini)");
                    nbPtsMax = LectureClavier.lireEntier("Entrez un nombre de points maximum (0=infini)");
                } while (nbJeuxMax == 0 && nbPtsMax == 0);

                Partie p = new Partie(nbJoueurs, nbJeuxMax, nbPtsMax);
                int i;
                /* On demande le nom des vrais joueurs et on les ajoute à la partie */
                for (i = 0; i < nbJoueurs - nbIA; i++) {
                    System.out.println("Nom du joueur n°" + (i + 1));
                    String nom = LectureClavier.lireChaine();
                    p.ajoutJoueur(new Joueur(nom, false));
                }

                /* On crée le nombre de joueurs IA nécessaires */
                for (int j = i; j < nbJoueurs; j++) {
                    System.out.println("Nom du joueur ordinateur n°" + (j + 1));
                    p.ajoutJoueur(new Joueur("Joueur " + (j + 1), true));
                }
                p.lancerPartie();
            default:
                break;
        }
    }

}
