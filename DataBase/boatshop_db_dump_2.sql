-- MySQL dump 10.13  Distrib 8.0.13, for osx10.13 (x86_64)
--
-- Host: localhost    Database: boatshop
-- ------------------------------------------------------
-- Server version	8.0.13

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
 SET NAMES utf8mb4 ;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `boats`
--

DROP TABLE IF EXISTS `boats`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `boats` (
  `bid` int(11) NOT NULL,
  `name` varchar(40) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `color` varchar(20) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`bid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `boats`
--

LOCK TABLES `boats` WRITE;
/*!40000 ALTER TABLE `boats` DISABLE KEYS */;
INSERT INTO `boats` VALUES (1,'Cormorant, great','Turquoise'),(2,'Red-necked wallaby','Violet'),(3,'Jungle cat','Fuscia'),(4,'King vulture','Blue'),(5,'Mourning collared dove','Goldenrod'),(6,'Heron, grey','Aquamarine'),(7,'Wombat, southern hairy-nosed','Violet'),(8,'White-tailed jackrabbit','Aquamarine'),(9,'California sea lion','Mauv'),(10,'Hornbill, southern ground','Aquamarine'),(11,'Flycatcher, tyrant','Green'),(12,'Ocelot','Green'),(13,'Goldeneye, barrows','Mauv'),(14,'Blue peacock','Red'),(15,'Crested bunting','Aquamarine'),(16,'Osprey','Goldenrod'),(17,'Eastern indigo snake','Maroon'),(18,'Kangaroo, jungle','Aquamarine'),(19,'Cobra, cape','Aquamarine'),(20,'Leopard, indian','Maroon');
/*!40000 ALTER TABLE `boats` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reservations`
--

DROP TABLE IF EXISTS `reservations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `reservations` (
  `sid` int(11) NOT NULL,
  `bid` int(11) NOT NULL,
  `date` date NOT NULL,
  PRIMARY KEY (`sid`,`bid`,`date`),
  KEY `bid` (`bid`),
  CONSTRAINT `reservations_ibfk_1` FOREIGN KEY (`sid`) REFERENCES `sailors` (`sid`),
  CONSTRAINT `reservations_ibfk_2` FOREIGN KEY (`bid`) REFERENCES `boats` (`bid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reservations`
--

LOCK TABLES `reservations` WRITE;
/*!40000 ALTER TABLE `reservations` DISABLE KEYS */;
INSERT INTO `reservations` VALUES (6,1,'2018-01-29'),(5,2,'2018-10-19'),(9,2,'2018-08-01'),(4,3,'2018-09-01'),(6,3,'2018-07-17'),(1,4,'2018-09-27'),(2,5,'2018-09-08'),(3,5,'2018-02-21'),(4,5,'2018-07-26'),(8,5,'2018-11-25'),(6,6,'2018-04-16'),(9,7,'2018-04-03'),(5,8,'2018-11-19'),(2,9,'2018-09-29'),(6,9,'2018-09-08'),(4,11,'2018-08-04'),(9,11,'2018-06-05'),(5,12,'2018-10-01'),(3,13,'2018-10-25'),(6,13,'2018-11-30'),(2,14,'2018-02-03'),(4,14,'2018-04-09'),(7,15,'2018-11-15'),(9,15,'2018-03-26'),(3,16,'2018-04-09'),(8,16,'2018-11-28'),(1,17,'2018-09-22'),(1,17,'2018-10-03'),(1,17,'2018-10-11'),(2,17,'2019-01-22'),(4,18,'2018-06-30'),(5,18,'2018-05-22'),(5,19,'2018-02-09'),(8,19,'2018-08-30'),(1,20,'2018-12-23'),(2,20,'2018-04-22'),(6,20,'2018-01-29'),(7,20,'2018-08-05'),(8,20,'2018-07-09'),(8,20,'2018-09-17');
/*!40000 ALTER TABLE `reservations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sailors`
--

DROP TABLE IF EXISTS `sailors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `sailors` (
  `sid` int(11) NOT NULL,
  `name` varchar(40) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `rating` int(11) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `yrssailed` int(11) DEFAULT NULL,
  PRIMARY KEY (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sailors`
--

LOCK TABLES `sailors` WRITE;
/*!40000 ALTER TABLE `sailors` DISABLE KEYS */;
INSERT INTO `sailors` VALUES (1,'Belva Skirvin',42,24,3),(2,'Kippar Bosence',55,22,3),(3,'Fergus Kops',79,25,1),(4,'Jacky Beggan',42,31,5),(5,'Padgett Leicester',15,22,1),(6,'Jacky Beggan',20,25,4),(7,'Welby Fontaine',70,24,1),(8,'Lucky Garretson',74,27,5),(9,'Chryste Weeks',12,25,2),(10,'Black Beard',41,40,15);
/*!40000 ALTER TABLE `sailors` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
