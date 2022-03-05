-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3307
-- Généré le : sam. 05 mars 2022 à 14:44
-- Version du serveur :  10.4.13-MariaDB
-- Version de PHP : 7.4.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `projet i4 iot`
--

-- --------------------------------------------------------

--
-- Structure de la table `donnees`
--

DROP TABLE IF EXISTS `donnees`;
CREATE TABLE IF NOT EXISTS `donnees` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `rfid1` int(11) DEFAULT NULL,
  `rfid2` int(11) DEFAULT NULL,
  `rfid3` int(11) DEFAULT NULL,
  `rfid4` int(11) DEFAULT NULL,
  `rfid5` int(11) DEFAULT NULL,
  `acces` int(11) DEFAULT NULL,
  `date` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=122 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `donnees`
--

INSERT INTO `donnees` (`id`, `rfid1`, `rfid2`, `rfid3`, `rfid4`, `rfid5`, `acces`, `date`) VALUES
(114, 17, 34, 51, 68, 85, 0, '2022-02-24 14:39:25'),
(116, 125, 239, 45, 237, 8, 0, '2022-02-24 16:40:14'),
(117, 125, 239, 45, 237, 8, 0, '2022-02-24 16:43:08'),
(118, 221, 170, 42, 237, 8, 0, '2022-02-24 16:46:07'),
(119, 125, 239, 45, 237, 8, 0, '2022-02-24 16:51:37'),
(120, 125, 239, 45, 237, 8, 0, '2022-02-24 16:52:46'),
(121, 236, 192, 170, 105, 42, 1, '2022-02-24 16:59:47'),
(115, 236, 192, 170, 105, 42, 1, '2022-02-24 14:40:14');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
