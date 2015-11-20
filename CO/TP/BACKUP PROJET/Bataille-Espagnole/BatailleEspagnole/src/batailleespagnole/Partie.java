package batailleespagnole;

import java.util.ArrayList;
import java.util.Map.Entry;

// <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
// #[regen=yes,id=DCE.82ECEC05-F078-B9D4-40D2-A7DE9C6BBD5E]
// </editor-fold> 
public class Partie {

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.0CB79760-CADB-EFCE-9702-D4649575945F]
    // </editor-fold> 
    private int nbJeux;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.2ED3DC27-A0FA-F9C8-F738-6EAF3548133A]
    // </editor-fold> 
    private int nbPointsMax;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.FD48E22F-8151-943A-BC2D-1120127A062E]
    // </editor-fold> 
    private ArrayList<Jeu> mJeu;

    private final int nbJoueurs;

    static final int NB_CARTES = 52;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.41806A56-6E71-2568-2CC1-3C00DF0D9BCB]
    // </editor-fold> 
    private ArrayList<Joueur> mJoueurs;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.99CAE846-9944-0EE3-736F-37812BED87D3]
    // </editor-fold> 
    public Partie(int nbJoueurs) {
        this.nbJoueurs = nbJoueurs;
        this.nbJeux = 10;
        this.nbPointsMax = 300;

        this.mJeu = new ArrayList<>();
        this.mJoueurs = new ArrayList<>();
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.E30D0BAE-7F5D-C16E-E935-2B69C94A4676]
    // </editor-fold> 
    public Partie(int nbJoueurs, int nbJeux, int nbPointsMax) {
        this.nbJoueurs = nbJoueurs;
        this.nbJeux = nbJeux;
        this.nbPointsMax = nbPointsMax;

        this.mJeu = new ArrayList<>();
        this.mJoueurs = new ArrayList<>();
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.63A0D835-A956-0A99-E00F-2F8F16DDCF89]
    // </editor-fold> 
    public int getNbJeux() {
        return nbJeux;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.2080C94F-5214-795D-4139-137A26358E4E]
    // </editor-fold> 
    public void setNbJeux(int val) {
        this.nbJeux = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.C2E3B0C5-441F-EDEC-8296-232F81F1A01E]
    // </editor-fold> 
    public int getNbPointsMax() {
        return nbPointsMax;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.3C29BD50-C0C6-36D6-B355-D4375C5FD600]
    // </editor-fold> 
    public void setNbPointsMax(int val) {
        this.nbPointsMax = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.1CCC8F6A-B92D-EAE7-F18C-0FF8236446E0]
    // </editor-fold> 
    public int getNbJoueurs() {
        return this.nbJoueurs;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.18136978-E2CA-EB0A-FB50-1D3AB950D1AA]
    // </editor-fold> 
    public ArrayList<Jeu> getJeu() {
        return mJeu;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.6D64864B-AE86-BBDA-61E6-9957DCBB51FF]
    // </editor-fold> 
    public void setJeu(ArrayList<Jeu> val) {
        this.mJeu = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.55EAECAC-85EB-7EA1-B923-2020077C5418]
    // </editor-fold> 
    public ArrayList<Joueur> getJoueurs() {
        return mJoueurs;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.DF758A1B-1157-4C93-8FC7-F39946E40493]
    // </editor-fold> 
    public void setJoueurs(ArrayList<Joueur> val) {
        this.mJoueurs = val;
    }

    public void ajoutJoueur(Joueur j) {
        mJoueurs.add(j);
    }

    public void supprJoueur(Joueur j) {
        mJoueurs.remove(j);
    }

    public void lancerPartie() {
        mJoueurs.get(0).setPremier(true);
        int i = 0, max = 0;
        boolean cond;
        if (nbJeux != 0) {
            cond = i < nbJeux;
        } else {
            cond = max < nbPointsMax;
        }
        while (cond) {
            Jeu j = new Jeu(mJoueurs);
            j.creerPaquet();
            j.melangerCartes();
            j.distribuer(mJoueurs);
            j.determinerAtout(mJoueurs);
            /* appel à la fonction qui fait jouer les joueurs */
            while (!j.finJeu(mJoueurs)) {
                j.jouerTour(mJoueurs);
                Joueur jWin = j.determinerVainqueur();

                /* On remet les attributs premier des joueurs à false */
                for (int k = 0; k < mJoueurs.size(); k++) {
                    mJoueurs.get(k).setPremier(false);
                }
                jWin.setPremier(true);

                System.out.println("Le vainqueur du pli n°" + ((j.getNbPlis()) + 1) + " est " + jWin.getNom());
                j.setNbPlis(j.getNbPlis() + 1);
                for (Entry<Joueur, Carte> e : j.getPliActuel().entrySet()) {
                    jWin.getPlisGagnes().add(e.getValue());
                }
                /* On vide le pli actuel */
                j.getPliActuel().clear();
            }
            j.compterPoints(mJoueurs);
            Joueur jWin = null;
            for (int k = 0; k < mJoueurs.size(); k++) {
                if (mJoueurs.get(k).getNbPoints() > max) {
                    max = mJoueurs.get(k).getNbPoints();
                    jWin = mJoueurs.get(k);
                }
            }
            tableauScores();
            System.out.println("Le vainqueur du jeu n°" + (i + 1) + " est " + jWin.getNom());

            /* Iteration de la boucle */
            i++;

            /* On reteste la condition */
            if (nbJeux != 0) {
                cond = i < nbJeux;
            } else {
                cond = max < nbPointsMax;
            }
        }
    }

    public void tableauScores() {
        System.out.println("");
        for (int i = 0; i < mJoueurs.size(); i++) {
            System.out.println("<" + mJoueurs.get(i).getNom() + "> => " + mJoueurs.get(i).getNbPoints() + " pts");
        }
    }
}
