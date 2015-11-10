package batailleespagnole;

import java.util.ArrayList; 

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

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.68E76D13-941C-AAF3-B239-77A2D7EB4A6C]
    // </editor-fold> 
    private boolean tour;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.19AA4D84-6B0A-E652-4FB4-AF29F726A31C]
    // </editor-fold> 
    private int Unnamed;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.BE6D8EFC-C7C8-5E18-76BD-752E80A886A7]
    // </editor-fold> 
    private ArrayList<Carte> mCarte;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.B1CC00A2-ECB6-67A4-6437-8C82AF977CFB]
    // </editor-fold> 
    private ArrayList<Partie> mPartie;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.FE59E101-615A-2947-7EA1-96F1F50371BE]
    // </editor-fold> 
    public Joueur () {
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.ADC6B0D9-0711-4AF3-7E77-6603908D43D9]
    // </editor-fold> 
    public ArrayList<Carte> getCarte () {
        return mCarte;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.D7E31F2A-853B-CCCC-7416-2CE4F29D3EA3]
    // </editor-fold> 
    public void setCarte (ArrayList<Carte> val) {
        this.mCarte = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.5B763AA0-337C-FCC8-7B08-FF7C4E142B78]
    // </editor-fold> 
    public ArrayList<Partie> getPartie () {
        return mPartie;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.4348DC49-88EC-2A08-1E73-F709231262CF]
    // </editor-fold> 
    public void setPartie (ArrayList<Partie> val) {
        this.mPartie = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.A75E7EE8-52B8-B972-69C2-271AB5C0C194]
    // </editor-fold> 
    public int getNbPoints () {
        return nbPoints;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.2CD0510C-C057-A5CB-1A97-01D965F2BFE2]
    // </editor-fold> 
    public void setNbPoints (int val) {
        this.nbPoints = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.7DCDEA3A-8EFA-3FCC-6BA3-F7E2B34A9FE9]
    // </editor-fold> 
    public String getNom () {
        return nom;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.E0A9BC8A-DD14-8DD5-6AED-1506876777BE]
    // </editor-fold> 
    public void setNom (String val) {
        this.nom = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.6269EE96-3386-EED8-E21C-281C5E4FE5C2]
    // </editor-fold> 
    public boolean getTour () {
        return tour;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.6A9CB9C3-23A0-612F-97C9-4ECE546CA1FA]
    // </editor-fold> 
    public void setTour (boolean val) {
        this.tour = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.1DAF6847-A28B-2D0E-5550-AA504F96E002]
    // </editor-fold> 
    public void jouer (Carte carte) {
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.D5451F0E-CF8C-0CD3-7590-145DAA5B4521]
    // </editor-fold> 
    public Carte piocher () {
        return null;
    }

}

