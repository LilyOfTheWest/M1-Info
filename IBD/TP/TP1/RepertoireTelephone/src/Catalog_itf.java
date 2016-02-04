/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Lily
 */
public interface Catalog_itf {
    int register(Person p);
    int delete(Person p);
    int getTel(Person p);
    String getAddress(Person p);
    /* … méthodes à ajouter à votre convenance */
}
