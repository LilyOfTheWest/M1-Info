/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tp2;

/**
 *
 * @author Lily
 */
public class TP2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Author a = new Author("Roger", "Dupont");
        Author b = new Author("Roge", "Dupont");
        
        if(a.equals(b))
            System.out.println("a = b");
        else System.out.println("a != b");
        
    }
    
}
