package tp2;

import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.Properties;

import com.jcraft.jsch.JSch;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;

public class Banque {
	
	static final String CONN_URL = "jdbc:oracle:thin:@im2ag-oracle.e.ujf-grenoble.fr:1521:ufrima";
	
	static final String USER = "pouvarel";
	static final String PASSWD = "bd2015";
        static final String strSshUser = USER;
        static final String strSshPassword = PASSWD;
        static final int nSshPort = 22;
        static final String strSshHost = "im2ag-oracle.e.ujf-grenoble.fr";
        static final String strRemoteHost ="pouvarel@im2ag-oracle.e.ujf-grenoble.fr";
	static final int nLocalPort = 1521;
        static final int nRemotePort = 1521;
        
	private static void menu() {
		System.out.println("*** Choisir une action a effectuer : ***");
		System.out.println("0 : Quitter");
		System.out.println("1 : Afficher la liste des animaux");
		System.out.println("2 : Deplacer un animal de cage");
		System.out.println("3 : Ajouter une maladie");
	}

	private static void listeAnimaux() throws SQLException {
		// A COMPLETER
            
	}

	private static void deplacerAnimal() throws SQLException {
		// A COMPLETER
	}	

	private static void ajouterMaladie() throws SQLException {
		// A COMPLETER
	}		


	private static void commit() throws SQLException {
		// A COMPLETER
	}				

	private static void rollback() throws SQLException {
		// A COMPLETER
	}		
	
	private static void getIsolation() throws SQLException {
		// A COMPLETER
	}

	private static void setIsolation() throws SQLException {
		// A COMPLETER
	}	
	
        private static void doSshTunnel( String strSshUser, String strSshPassword, String strSshHost, int nSshPort, String strRemoteHost, int nLocalPort, int nRemotePort ) throws JSchException{
        final JSch jsch = new JSch();
        Session session = jsch.getSession( strSshUser, strSshHost, 22 );
        session.setPassword( strSshPassword );

        final Properties config = new Properties();
        config.put( "StrictHostKeyChecking", "no" );
        session.setConfig( config );

        session.connect();
        session.setPortForwardingL(nLocalPort, strRemoteHost, nRemotePort);
        }
    public static void main(String args[]) {

        try {
        
        int action;
        boolean exit = false;

  	    // Enregistrement du driver Oracle
  	    System.out.print("Loading Oracle driver... "); 
  	    // A COMPLETER
            DriverManager.registerDriver(new oracle.jdbc.OracleDriver());
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
                Banque.doSshTunnel(strSshUser, strSshPassword, strSshHost, nSshPort, strRemoteHost, nLocalPort, nRemotePort);
            } catch (JSchException ex) {
                Logger.getLogger(Banque.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            Connection conn = DriverManager.getConnection(CONN_URL, USER, PASSWD);
            
  	    System.out.println("connected");
  	    
  	    // Desactivation de l'autocommit
  	    // A COMPLETER
  	    System.out.println("Autocommit disabled");

  	    while(!exit) {
  	    	menu();
  	    	action = LectureClavier.lireEntier("votre choix ?");
  	    	switch(action) {
  	    		case 0 : exit = true; break;
  	    		case 1 : listeAnimaux(); break;
  	    		case 2 : deplacerAnimal(); break;
  	    		case 3 : ajouterMaladie(); break;
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