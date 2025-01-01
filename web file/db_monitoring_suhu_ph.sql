-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 22, 2024 at 07:23 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_monitoring_suhu_ph`
--

-- --------------------------------------------------------

--
-- Table structure for table `dt_device`
--

CREATE TABLE `dt_device` (
  `Id` int(11) NOT NULL,
  `idDevice` varchar(5) DEFAULT NULL,
  `deviceName` varchar(255) DEFAULT NULL,
  `inputTime` timestamp NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `dt_sensor`
--

CREATE TABLE `dt_sensor` (
  `Id` int(11) NOT NULL,
  `idDevice` varchar(5) DEFAULT NULL,
  `suhu` double DEFAULT NULL,
  `ph` double DEFAULT NULL,
  `inputTime` timestamp NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `dt_sensor_detail`
--

CREATE TABLE `dt_sensor_detail` (
  `Id` int(11) NOT NULL,
  `idDevice` varchar(5) DEFAULT NULL,
  `suhu` double DEFAULT NULL,
  `ph` double DEFAULT NULL,
  `nilaiOutputSuhuUp` double DEFAULT NULL,
  `nilaiOutputSuhuDown` double DEFAULT NULL,
  `nilaiOutputPhStabilizer` double DEFAULT NULL,
  `statusRelaySuhuUp` varchar(2) DEFAULT NULL,
  `statusRelaySuhuDown` varchar(2) DEFAULT NULL,
  `statusRelayPhStabilizer` varchar(2) DEFAULT NULL,
  `inputTime` timestamp NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `dt_sensor_detail`
--

INSERT INTO `dt_sensor_detail` (`Id`, `idDevice`, `suhu`, `ph`, `nilaiOutputSuhuUp`, `nilaiOutputSuhuDown`, `nilaiOutputPhStabilizer`, `statusRelaySuhuUp`, `statusRelaySuhuDown`, `statusRelayPhStabilizer`, `inputTime`) VALUES
(13, '1', 27.38, 8.2, 31.25, 0, 100, '1', '0', '1', '2024-12-15 13:24:43'),
(14, '1', 27.31, 8.23, 34.38, 0, 100, '1', '0', '1', '2024-12-15 13:32:46'),
(15, '1', 27.38, 7.47, -0, 50, 300, '0', '1', '1', '2024-12-15 13:37:57'),
(16, '1', 27.31, 9.82, 34.38, 0, 100, '1', '0', '1', '2024-12-15 13:48:04'),
(17, '1', 27.38, 9.5, 31.25, 0, 100, '1', '0', '1', '2024-12-15 13:56:02'),
(18, '1', 27.38, 9.75, 31.25, 0, 100, '1', '0', '1', '2024-12-15 14:03:55'),
(19, '1', 27.38, 9.35, 31.25, 0, 100, '1', '0', '1', '2024-12-15 14:11:48'),
(20, '1', 27.38, 9.5, 31.25, 0, 100, '1', '0', '1', '2024-12-15 14:19:42'),
(21, '1', 27.38, 9.39, 31.25, 0, 100, '1', '0', '1', '2024-12-15 14:27:37'),
(22, '1', 27.31, 9.5, 34.38, 0, 100, '1', '0', '1', '2024-12-15 14:35:30'),
(23, '1', 27.94, 3.72, 3.13, 0, 100, '1', '0', '1', '2024-12-18 06:24:31'),
(24, '1', 27.94, -4.48, 3.13, 0, 100, '1', '0', '1', '2024-12-18 06:25:47'),
(25, '1', 27.94, 4.98, 3.13, 0, 100, '1', '0', '1', '2024-12-18 06:32:59'),
(26, '1', 27.94, 2.92, 3.13, 0, 100, '1', '0', '1', '2024-12-18 06:41:59');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `dt_device`
--
ALTER TABLE `dt_device`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `dt_sensor`
--
ALTER TABLE `dt_sensor`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `dt_sensor_detail`
--
ALTER TABLE `dt_sensor_detail`
  ADD PRIMARY KEY (`Id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `dt_device`
--
ALTER TABLE `dt_device`
  MODIFY `Id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `dt_sensor`
--
ALTER TABLE `dt_sensor`
  MODIFY `Id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `dt_sensor_detail`
--
ALTER TABLE `dt_sensor_detail`
  MODIFY `Id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
