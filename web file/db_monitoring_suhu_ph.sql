# Host: localhost  (Version 5.5.5-10.4.32-MariaDB)
# Date: 2024-12-15 03:04:36
# Generator: MySQL-Front 6.0  (Build 2.20)


#
# Structure for table "dt_device"
#

DROP TABLE IF EXISTS `dt_device`;
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

DROP TABLE IF EXISTS `dt_sensor`;
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

