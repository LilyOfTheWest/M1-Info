/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tp2;

import java.util.Objects;

/**
 *
 * @author Lily
 */
public class Author {
    private final String firstName;
    private final String lastName;

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }
  
   
    public Author(String firstName,  String lastName){
        this.firstName = Objects.requireNonNull(firstName, "Le prenom ne doit pas être null");
        this.lastName = Objects.requireNonNull(lastName, "Le nom ne doit pas être null");
    }

    public boolean equals(Object o){
        if(!(o instanceof Author)){
            return false;
        }
        
    Author author = (Author)o;
    return (author.firstName.equals(this.firstName) && author.lastName.equals(this.lastName));
    }
}