package batailleespagnole;

// <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
// #[regen=yes,id=DCE.6384B198-9A51-156D-F380-21276E467CE3]
// </editor-fold> 
public class Carte implements Comparable {

    static enum TypeOrdre {

        DEUX, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, DIX, CAVALIER, DAME, ROI, TROIS, AS;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.94E54F8B-922C-A362-FFC7-336B808D8B63]
    // </editor-fold> 
    private TypeOrdre ordre;

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,id=DCE.EB3D496D-A648-B074-ECDB-8BFBD8AA17D5]
    // </editor-fold> 
    private int valeur;

    private TypeFamille famille;

    public Carte(TypeOrdre ordre, TypeFamille famille) {
        this.ordre = ordre;
        this.famille = famille;
        switch (ordre) {
            case AS:
                this.valeur = 11;
                break;
            case TROIS:
                this.valeur = 10;
                break;
            case ROI:
                this.valeur = 4;
                break;
            case DAME:
                this.valeur = 3;
                break;
            case CAVALIER:
                this.valeur = 2;
                break;
            case DIX:
            case NEUF:
            case HUIT:
            case SEPT:
            case SIX:
            case CINQ:
            case QUATRE:
            case DEUX:
                this.valeur = 0;
                break;
            default:
                System.err.println("Erreur : ordre de carte inexistant");
        }
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.4B0892EA-7CCC-BD9C-0057-36BCE26BA1F5]
    // </editor-fold> 
    public TypeOrdre getOrdre() {
        return ordre;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.AFF1BB55-8CB5-1724-8640-68D544841CB7]
    // </editor-fold> 
    public void setOrdre(TypeOrdre val) {
        this.ordre = val;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.B1A3DC70-FE6B-0E95-DB5D-D9472652FCAF]
    // </editor-fold> 
    public int getValeur() {
        return valeur;
    }

    // <editor-fold defaultstate="collapsed" desc=" UML Marker "> 
    // #[regen=yes,regenBody=yes,id=DCE.1F2E7405-F0A5-31D5-43FD-4A200F91DABE]
    // </editor-fold> 
    public void setValeur(int val) {
        this.valeur = val;
    }

    public TypeFamille getFamille() {
        return famille;
    }

    public void setFamille(TypeFamille famille) {
        this.famille = famille;
    }

    @Override
    public int compareTo(Object o) {
        if (((Carte) o).getFamille() == this.famille) {
            return this.getOrdre().compareTo(((Carte) o).getOrdre());
        }
        return -1;
    }

    @Override
    public String toString() {
        String s = "";
        s = ordre.toString() + " de " + famille.toString();

        return s;
    }
}
