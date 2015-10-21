package tp2;

import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.Properties;

public class Banque {
	static Connection conn;
	static final String CONN_URL = "jdbc:oracle:thin:@localhost:1521";
	
	static final String USER = "pouvarel";
	static final String PASSWD = "bd2015";
        

	private static void menu() {
		System.out.println("*** Choisir une action a effectuer : ***");
		System.out.println("0 : Quitter");
		System.out.println("1 : Afficher la liste des animaux");
		System.out.println("2 : Deplacer un animal de cage");
		System.out.println("3 : Ajouter une maladie");
                System.out.println("4 : Valider la transaction");
                System.out.println("5 : Annuler la transaction");
	}

	private static void listeAnimaux() throws SQLException {
            Statement st = conn.createStatement();

            ResultSet rs = st.executeQuery("SELECT * FROM LesAnimaux");
            System.out.println("Liste de tous les animaux");

            afficherRes(rs);       
            System.out.println();
            st.close();
	}

	private static void deplacerAnimal() throws SQLException {
            String animal;
            int cage;
            System.out.println("Quel animal voulez-vous déplacer ?");
            animal = LectureClavier.lireChaine();
            cage = LectureClavier.lireEntier("Vers quel numéro de cage voulez-vous déplacer "+animal+" ?");
            
            Statement st = conn.createStatement();
            
            int nb = st.executeUpdate("UPDATE LesAnimaux SET noCage="+cage+" WHERE noma='"+animal+"'");         
            System.out.println(nb + " ligne (s) modifiée (s).");      
            
            st.close();
	}	

	private static void ajouterMaladie() throws SQLException {
            String animal, maladie;
            System.out.println("A quel animal souhaitez-vous ajouter une maladie ?");
            animal = LectureClavier.lireChaine();
            System.out.println("Quelle maladie souhaitez-vous ajouter ?");
            maladie = LectureClavier.lireChaine();
            
            Statement st = conn.createStatement();

            int nb = st.executeUpdate("INSERT INTO LesMaladies VALUES('"+animal+"', '"+maladie+"')");
            System.out.println(nb + " ligne (s) ajoutée (s) dans LesMaladies.");
            System.out.println();
            st.close();
	}		


	private static void commit() throws SQLException {
		// A COMPLETER
            conn.commit();
            System.out.println("Transaction validée");
	}				

	private static void rollback() throws SQLException {
		// A COMPLETER
            conn.rollback();
            System.out.println("Transaction annulée");
	}		
	
	private static void getIsolation() throws SQLException {
		// A COMPLETER
            int level = conn.getTransactionIsolation();
            
            System.out.print("Niveau d'isolation : ");
            switch(level){
                case Connection.TRANSACTION_READ_COMMITTED:
                    System.out.println("READ COMMITTED");
                    break;
                case Connection.TRANSACTION_READ_UNCOMMITTED:
                    System.out.println("READ UNCOMMITTED");
                    break;
                case Connection.TRANSACTION_REPEATABLE_READ:
                    System.out.println("REPEATABLE READ");
                    break;
                case Connection.TRANSACTION_SERIALIZABLE:
                    System.out.println("SERIALIZABLE");
                    break;
                default:
                    break;
            }
	}

	private static void setIsolation() throws SQLException {
		// A COMPLETER
            System.out.println("*** Choisir un niveau d'isolation : ***");
            System.out.println("0 : READ_UNCOMMITTED");
            System.out.println("1 : READ_COMMITTED");
            System.out.println("2 : REPEATABLE_READ");
            System.out.println("3 : SERIALIZABLE");
                  
            int level = LectureClavier.lireEntier("Entrez un entier");
            boolean ok = true;
            
            switch(level){
                case 0: level=Connection.TRANSACTION_READ_UNCOMMITTED; break;
                case 1: level=Connection.TRANSACTION_READ_COMMITTED; break;
                case 2: level=Connection.TRANSACTION_REPEATABLE_READ; break;
                case 3: level=Connection.TRANSACTION_SERIALIZABLE; break;
                default: System.out.println("Pas le bon numéro");ok=false; break;
                
            }
            if(ok)
                conn.setTransactionIsolation(level);
	}	
        
        public static void afficherRes(ResultSet rs){
            try {
                    ResultSetMetaData rms = rs.getMetaData();
                    int col = rms.getColumnCount();

                    for(int i=1; i <= col; i++) {
                            String nomCol = rms.getColumnName(i);
                            System.out.print(String.format("%-15s", nomCol));
                    }
                    System.out.println();
                    
                    for(int i=1; i <= col; i++) {
                            System.out.print("--------------");
                    }
                    System.out.println();

                    while(rs.next()) {
                            for(int i=1; i <= col; i++) {
                                    String type = rms.getColumnClassName(i);
                                    
                                    if (type.equals("java.lang.String")) {
                                            System.out.print(String.format("%-15s", rs.getString(i)));
                                    } else if (type.equals("java.math.BigDecimal")) {
                                            System.out.print(String.format("%-15s", String.valueOf(rs.getInt(i))));                                  
                                    } else if (type.equals("java.sql.Date")) {
                                            System.out.print(String.format("%-15s", rs.getDate(i)));
                                    }                             
                            }
                            System.out.println();
                    }
            } catch (SQLException e) {
                    System.out.println("ERREUR : " + e.getMessage());
            }
        }
        
    public static void main(String args[]) {

       
        
        int action;
        boolean exit = false;

  	    // Enregistrement du driver Oracle
  	    System.out.print("Loading Oracle driver... "); 
            try {
                // A COMPLETER
                DriverManager.registerDriver(new oracle.jdbc.OracleDriver());
            } catch (SQLException ex) {
                Logger.getLogger(Banque.class.getName()).log(Level.SEVERE, null, ex);
            }
            try {
                Class.forName("oracle.jdbc.OracleDriver").newInstance();
            } catch (InstantiationException ex) {
                Logger.getLogger(Banque.class.getName()).log(Level.SEVERE, null, ex);
            } catch (IllegalAccessException ex) {
                Logger.getLogger(Banque.class.getName()).log(Level.SEVERE, null, ex);
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(Banque.class.getName()).log(Level.SEVERE, null, ex);
            }
  	    System.out.println("loaded");
  	    
  	    // Etablissement de la connection
  	    System.out.print("Connecting to the database... "); 
            try {
                // A COMPLETER
            conn = DriverManager.getConnection(CONN_URL, USER, PASSWD);
            
  	    System.out.println("connected");
  	    
  	    // Desactivation de l'autocommit
  	    // A COMPLETER
  	    System.out.println("Autocommit disabled");
            conn.setAutoCommit(false);

  	    while(!exit) {
  	    	menu();
  	    	action = LectureClavier.lireEntier("votre choix ?");
  	    	switch(action) {
  	    		case 0 : exit = true; break;
  	    		case 1 : listeAnimaux(); break;
  	    		case 2 : deplacerAnimal(); break;
  	    		case 3 : ajouterMaladie(); break;
                        case 4 : commit(); break;
                        case 5 : rollback(); break;
  	    		default : System.out.println("=> choix incorrect"); menu();
  	    	}
  	    } 	    

  	    // Liberation des ressources et fermeture de la connexion...
		// A COMPLETER
  	    
  	    System.out.println("au revoir");
  	    
  	    // traitement d'exception
          } catch (SQLException e) {
              System.err.println("failed");
              System.out.println("Affichage de la pile d'erreur");
  	          e.printStackTrace(System.err);
              System.out.println("Affichage du message d'erreur");
              System.out.println(e.getMessage());
              System.out.println("Affichage du code d'erreur");
  	          System.out.println(e.getErrorCode());	    

          }
    }

}