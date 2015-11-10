package batailleespagnole;


// <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
// #[regen=yes,id=DCE.6384B198-9A51-156D-F380-21276E467CE3]
// </editor-fold> 
public class Carte {

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.94E54F8B-922C-A362-FFC7-336B808D8B63]
    // </editor-fold> 
    private int ordre;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.EB3D496D-A648-B074-ECDB-8BFBD8AA17D5]
    // </editor-fold> 
    private int valeur;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.83844F18-BE86-277D-F532-D6B0CEC29AC2]
    // </editor-fold> 
    private Joueur mJoueur;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.A46820AC-CBAD-1A61-F60E-47CAD2081B96]
    // </editor-fold> 
    public Carte () {
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.4610DEA3-26AF-1381-F57B-AEEED9483041]
    // </editor-fold> 
    public Joueur getJoueur () {
        return mJoueur;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.DA5E8A9B-B4FE-841E-FEE4-5FD75C0B9325]
    // </editor-fold> 
    public void setJoueur (Joueur val) {
        this.mJoueur = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.4B0892EA-7CCC-BD9C-0057-36BCE26BA1F5]
    // </editor-fold> 
    public int getOrdre () {
        return ordre;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.AFF1BB55-8CB5-1724-8640-68D544841CB7]
    // </editor-fold> 
    public void setOrdre (int val) {
        this.ordre = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.B1A3DC70-FE6B-0E95-DB5D-D9472652FCAF]
    // </editor-fold> 
    public int getValeur () {
        return valeur;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.1F2E7405-F0A5-31D5-43FD-4A200F91DABE]
    // </editor-fold> 
    public void setValeur (int val) {
        this.valeur = val;
    }

}

