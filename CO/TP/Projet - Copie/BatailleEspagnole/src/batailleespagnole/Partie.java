package batailleespagnole;

import java.util.ArrayList; 

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

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.41806A56-6E71-2568-2CC1-3C00DF0D9BCB]
    // </editor-fold> 
    private Joueur mJoueur;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.99CAE846-9944-0EE3-736F-37812BED87D3]
    // </editor-fold> 
    public Partie () {
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.E30D0BAE-7F5D-C16E-E935-2B69C94A4676]
    // </editor-fold> 
    public Partie (int nbJoueurs) {
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.63A0D835-A956-0A99-E00F-2F8F16DDCF89]
    // </editor-fold> 
    public int getNbJeux () {
        return nbJeux;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.2080C94F-5214-795D-4139-137A26358E4E]
    // </editor-fold> 
    public void setNbJeux (int val) {
        this.nbJeux = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.C2E3B0C5-441F-EDEC-8296-232F81F1A01E]
    // </editor-fold> 
    public int getNbPointsMax () {
        return nbPointsMax;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.3C29BD50-C0C6-36D6-B355-D4375C5FD600]
    // </editor-fold> 
    public void setNbPointsMax (int val) {
        this.nbPointsMax = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.1CCC8F6A-B92D-EAE7-F18C-0FF8236446E0]
    // </editor-fold> 
    public int getNbJoueurs () {
        return 0;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.18136978-E2CA-EB0A-FB50-1D3AB950D1AA]
    // </editor-fold> 
    public ArrayList<Jeu> getJeu () {
        return mJeu;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.6D64864B-AE86-BBDA-61E6-9957DCBB51FF]
    // </editor-fold> 
    public void setJeu (ArrayList<Jeu> val) {
        this.mJeu = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.55EAECAC-85EB-7EA1-B923-2020077C5418]
    // </editor-fold> 
    public Joueur getJoueur () {
        return mJoueur;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.DF758A1B-1157-4C93-8FC7-F39946E40493]
    // </editor-fold> 
    public void setJoueur (Joueur val) {
        this.mJoueur = val;
    }

}

