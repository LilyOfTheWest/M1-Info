
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Lily
 */
public class Catalog implements Catalog_itf{
    private ArrayList<Person> rep;
    
    
    @Override
    public int register(Person p) {
        if(rep.add(p))
            return 1;
        return 0;
    }

    @Override
    public int delete(Person p) {
        if(rep.remove(p)){
            return 1;
        }
        return 0;
}

    @Override
    public int getTel(Person p) {
        int index;
        if((index = rep.indexOf(p)) == -1){
            return 0;
        }
        return rep.get(index).getPhoneNumber();
    }

    @Override
    public String getAddress(Person p) {
        int index;
        if((index = rep.indexOf(p)) == -1){
            return "Nom inconnu du répertoire";
        }
        return rep.get(index).getAdress();
    }
    
}
