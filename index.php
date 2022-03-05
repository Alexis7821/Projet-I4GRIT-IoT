<?php  
	require('parametres.php'); //connexion à la bdd
	date_default_timezone_set('Europe/Paris'); //bon fuseau horaire
?>

<!DOCTYPE HTML>
<html>
	<head>
		<meta http-equiv="refresh" content="5"/> <!-- Rafraichissement automatique de la page -->
		<link rel="stylesheet" type="text/css" href="style.css">
		<link href='https://unpkg.com/boxicons@2.0.7/css/boxicons.min.css' rel='stylesheet'> <!-- Style des icones -->
		<link rel="stylesheet" href="Css/font-awesome-4.7.0/css/font-awesome.min.css">
		<script src="https://unpkg.com/boxicons@latest/dist/boxicons.js"></script> <!-- js des icones -->
		<title>Projet IOT - Modesto & MOURLANETTE </title>
	</head>
     <body>
		<h1>Visualisation des données</h1>
		<?php
			/*Selection de toutes les informations présentes*/
			$information = $pdo->prepare("SELECT * FROM donnees ORDER BY id DESC");
			$information->execute(array());
			$information = $information->fetchAll(); // on a les informations du profil;
			
			/*Récupération du nombre de lignes*/
			$nb_data = $pdo->prepare("SELECT COUNT(*) FROM donnees");
			$nb_data->execute();
			$nb_data = $nb_data->fetch();
			
			/*Test des valeurs de la carte : si c'est la bonne carte alors on autorise l'accès*/
			if($information[0]['rfid1'] == 236 && $information[0]['rfid2'] == 192 && $information[0]['rfid3'] == 170 && $information[0]['rfid4'] == 105 && $information[0]['rfid5'] == 42){ 
				$acces = $pdo->prepare("UPDATE donnees SET acces = :acces WHERE id = (SELECT MAX(id) FROM donnees)");
				$acces->execute(array('acces' => 1));
			}
			else{
				$acces = $pdo->prepare("UPDATE donnees SET acces = :acces WHERE id = (SELECT MAX(id) FROM donnees)");
				$acces->execute(array('acces' => 0));
			}
		?>
		<?php 
			/*Affichage des informations*/
			for($i = 0; $i < $nb_data[0]; $i++){ 
		?>
		<div id="infos" style= <?php if ($information[$i]['acces'] == 0) { ?>"background: #f54e2a;"<?php }?>>
			<p><b>ID : </b><?php echo $information[$i]['id'];?></p>
			<p><b>RFID : </b><?php echo $information[$i]['rfid1'];?>
			<?php echo $information[$i]['rfid2'];?>
			<?php echo $information[$i]['rfid3'];?>
			<?php echo $information[$i]['rfid4'];?>
			<?php echo $information[$i]['rfid5'];?></p>
			<p><b>ACCES : </b><?php echo $information[$i]['acces'];?>			
			<p><b>DATE : </b><?php echo $information[$i]['date'];?></p>
		</div>
		<?php 
			}
		?>
    </body>
</html>