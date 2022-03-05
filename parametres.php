<?php

session_start(); //début de la session


// Vos identifiants SQL
	define( 'MYSQL_HOST', 		'localhost' );
	define( 'MYSQL_DATABASE', 	'projet i4 iot' );
	define( 'MYSQL_USER',		'root' );
	define( 'MYSQL_PASSWORD',	'' ); // permet de créer les variables pour la connexion a la bdd

// Connexion à la base de donnée
	try {
		$strConnection = 'mysql:host='.MYSQL_HOST.';port=3307;dbname='.MYSQL_DATABASE; 		// Définition du serveur et de la base de donnée à se connecter
		$pdo = new PDO( $strConnection, MYSQL_USER, MYSQL_PASSWORD );				// Définition de l'utilisateur et mot de passe + connection
		$pdo->query( "SET NAMES 'utf8'" ); 											// On spécifie le type de caractère que l'on utilise
		$pdo->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING );				// On définie le signalement des erreurs
	} catch( PDOException $e ) {
		die( 'ERREUR PDO : ' . $e->getMessage() . ' => (Verifier les parametres de connexion)' );
	}
	
?>