package batailleespagnole;

import java.util.ArrayList;
import java.util.LinkedList;

// <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
// #[regen=yes,id=DCE.CC54FE1A-D482-F1F8-4BC2-0DB57B57C53A]
// </editor-fold> 
public class Joueur {

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.D6EBBA9C-A2DF-2EC7-ADDC-140CC30BCF12]
    // </editor-fold> 
    private String nom;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.078D6297-7935-837D-41DE-9C3839B0AA87]
    // </editor-fold> 
    private int nbPoints;

    private boolean premier;

    private boolean IA;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.BE6D8EFC-C7C8-5E18-76BD-752E80A886A7]
    // </editor-fold> 
    private ArrayList<Carte> cartesEnMain;

    private ArrayList<Carte> plisGagnes;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.B1CC00A2-ECB6-67A4-6437-8C82AF977CFB]
    // </editor-fold> 
    private Partie mPartie;

    public Joueur(String nom, boolean IA) {
        this.nom = nom;
        this.nbPoints = 0;
        this.premier = false;
        this.cartesEnMain = new ArrayList<>();
        this.plisGagnes = new ArrayList<>();
        this.IA = IA;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.5B763AA0-337C-FCC8-7B08-FF7C4E142B78]
    // </editor-fold> 
    public Partie getPartie() {
        return mPartie;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.4348DC49-88EC-2A08-1E73-F709231262CF]
    // </editor-fold> 
    public void setPartie(Partie val) {
        this.mPartie = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.A75E7EE8-52B8-B972-69C2-271AB5C0C194]
    // </editor-fold> 
    public int getNbPoints() {
        return nbPoints;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.2CD0510C-C057-A5CB-1A97-01D965F2BFE2]
    // </editor-fold> 
    public void setNbPoints(int val) {
        this.nbPoints = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.7DCDEA3A-8EFA-3FCC-6BA3-F7E2B34A9FE9]
    // </editor-fold> 
    public String getNom() {
        return nom;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.E0A9BC8A-DD14-8DD5-6AED-1506876777BE]
    // </editor-fold> 
    public void setNom(String val) {
        this.nom = val;
    }

    public void ajoutPoints(int val) {
        this.nbPoints += val;
    }

    public boolean isPremier() {
        return premier;
    }

    public void setPremier(boolean premier) {
        this.premier = premier;
    }

    public ArrayList<Carte> getCartesEnMain() {
        return cartesEnMain;
    }

    public void setCartesEnMain(ArrayList<Carte> cartesEnMain) {
        this.cartesEnMain = cartesEnMain;
    }

    public ArrayList<Carte> getPlisGagnes() {
        return plisGagnes;
    }

    public void setPlisGagnes(ArrayList<Carte> plisGagnes) {
        this.plisGagnes = plisGagnes;
    }

    public Partie getmPartie() {
        return mPartie;
    }

    public void setmPartie(Partie mPartie) {
        this.mPartie = mPartie;
    }

    public boolean isIA() {
        return IA;
    }

    public void setIA(boolean IA) {
        this.IA = IA;
    }

    @Override
    public boolean equals(Object o) {
        if (((Joueur) o).getNom().equals(this.nom) && ((Joueur) o).isIA() == this.IA) {
            return true;
        }
        return false;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.1DAF6847-A28B-2D0E-5550-AA504F96E002]
    // </editor-fold> 
    public Carte jouer(Carte carte) {
        cartesEnMain.remove(carte);

        return carte;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.D5451F0E-CF8C-0CD3-7590-145DAA5B4521]
    // </editor-fold> 
    public Carte piocher(LinkedList<Carte> tasDeCartes) {
        /* Si le tas est vide */
        if (tasDeCartes.isEmpty()) {
            /* le jeu est fini */
            /* ajouter exceptions */
        }

        /* Si le joueur a déjà trois cartes en main */
        if (cartesEnMain.size() == 3) {
            /* On lui donne rien */
            /* ajouter exceptions */
        }
        Carte c = tasDeCartes.pop();
        cartesEnMain.add(c);
        return c;
    }

}
