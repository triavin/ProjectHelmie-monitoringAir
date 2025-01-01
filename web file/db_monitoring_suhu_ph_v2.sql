# Host: localhost  (Version 5.5.5-10.4.32-MariaDB)
# Date: 2024-12-22 13:18:25
# Generator: MySQL-Front 6.0  (Build 2.20)


#
# Structure for table "dt_device"
#

CREATE TABLE `dt_device` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `idDevice` varchar(5) DEFAULT NULL,
  `deviceName` varchar(255) DEFAULT NULL,
  `inputTime` timestamp NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

#
# Data for table "dt_device"
#


#
# Structure for table "dt_sensor"
#

CREATE TABLE `dt_sensor` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `idDevice` varchar(5) DEFAULT NULL,
  `suhu` double DEFAULT NULL,
  `ph` double DEFAULT NULL,
  `inputTime` timestamp NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

#
# Data for table "dt_sensor"
#


#
# Structure for table "dt_sensor_detail"
#

CREATE TABLE `dt_sensor_detail` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `idDevice` varchar(5) DEFAULT NULL,
  `suhu` double DEFAULT NULL,
  `ph` double DEFAULT NULL,
  `nilaiOutputSuhuUp` double DEFAULT NULL,
  `nilaiOutputSuhuDown` double DEFAULT NULL,
  `nilaiOutputPhStabilizer` double DEFAULT NULL,
  `statusRelaySuhuUp` varchar(2) DEFAULT NULL,
  `statusRelaySuhuDown` varchar(2) DEFAULT NULL,
  `statusRelayPhStabilizer` varchar(2) DEFAULT NULL,
  `inputTime` timestamp NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

#
# Data for table "dt_sensor_detail"
#

INSERT INTO `dt_sensor_detail` VALUES (13,'1',27.38,8.2,31.25,0,100,'1','0','1','2024-12-15 20:24:43'),(14,'1',27.31,8.23,34.38,0,100,'1','0','1','2024-12-15 20:32:46'),(15,'1',27.38,7.47,-0,50,300,'0','1','1','2024-12-15 20:37:57'),(16,'1',27.31,9.82,34.38,0,100,'1','0','1','2024-12-15 20:48:04'),(17,'1',27.38,9.5,31.25,0,100,'1','0','1','2024-12-15 20:56:02'),(18,'1',27.38,9.75,31.25,0,100,'1','0','1','2024-12-15 21:03:55'),(19,'1',27.38,9.35,31.25,0,100,'1','0','1','2024-12-15 21:11:48'),(20,'1',27.38,9.5,31.25,0,100,'1','0','1','2024-12-15 21:19:42'),(21,'1',27.38,9.39,31.25,0,100,'1','0','1','2024-12-15 21:27:37'),(22,'1',27.31,9.5,34.38,0,100,'1','0','1','2024-12-15 21:35:30'),(23,'1',27.94,3.72,3.13,0,100,'1','0','1','2024-12-18 13:24:31'),(24,'1',27.94,-4.48,3.13,0,100,'1','0','1','2024-12-18 13:25:47'),(25,'1',27.94,4.98,3.13,0,100,'1','0','1','2024-12-18 13:32:59'),(26,'1',27.94,2.92,3.13,0,100,'1','0','1','2024-12-18 13:41:59');
