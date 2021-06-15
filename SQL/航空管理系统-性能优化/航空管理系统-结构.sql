/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 50710
 Source Host           : localhost:3306
 Source Schema         : Aviation management system

 Target Server Type    : MySQL
 Target Server Version : 50710
 File Encoding         : 65001

 Date: 11/06/2020 19:13:51
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for Account
-- ----------------------------
DROP TABLE IF EXISTS `Account`;
CREATE TABLE `Account` (
  `Account_id` varchar(40) NOT NULL,
  `Account_balance` decimal(13,2) NOT NULL,
  PRIMARY KEY (`Account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of Account
-- ----------------------------
BEGIN;
INSERT INTO `Account` VALUES ('1234567', 150.00);
INSERT INTO `Account` VALUES ('1234568', 21.21);
INSERT INTO `Account` VALUES ('1234569', 300.00);
COMMIT;

-- ----------------------------
-- Table structure for Flight
-- ----------------------------
DROP TABLE IF EXISTS `Flight`;
CREATE TABLE `Flight` (
  `Flight_id` varchar(40) NOT NULL,
  `Departure_city` varchar(40) NOT NULL,
  `Scheduled_arriving_city` varchar(40) NOT NULL,
  `Actual_arriving_city` varchar(40) DEFAULT NULL,
  `Scheduled_departure_time` datetime(6) NOT NULL,
  `Scheduled_arriving_time` datetime(6) NOT NULL,
  `Actual_arriving_time` datetime(6) DEFAULT NULL,
  `Actual_departure_time` datetime(6) DEFAULT NULL,
  PRIMARY KEY (`Flight_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of Flight
-- ----------------------------
BEGIN;
INSERT INTO `Flight` VALUES ('1', '上海', '北京', NULL, '2020-05-07 10:10:10.000000', '2020-05-07 12:10:10.000000', NULL, NULL);
INSERT INTO `Flight` VALUES ('2', '上海', '南京', '南京', '2020-05-07 10:11:11.000000', '2020-05-07 11:10:10.000000', '2020-05-07 11:10:12.000000', '2020-05-07 10:11:00.000000');
INSERT INTO `Flight` VALUES ('3', '上海', '东京', NULL, '2020-05-07 10:10:10.000000', '2020-05-07 14:10:10.000000', NULL, NULL);
INSERT INTO `Flight` VALUES ('4', '上海', '北京', NULL, '2020-05-07 11:30:20.000000', '2020-05-07 15:00:30.000000', NULL, NULL);
INSERT INTO `Flight` VALUES ('5', '上海', '北京', NULL, '2020-05-20 10:00:00.000000', '2020-05-21 10:00:00.000000', NULL, NULL);
COMMIT;

-- ----------------------------
-- Table structure for Flight_State
-- ----------------------------
DROP TABLE IF EXISTS `Flight_State`;
CREATE TABLE `Flight_State` (
  `Flight_id` varchar(40) NOT NULL,
  `State_id` varchar(40) NOT NULL,
  PRIMARY KEY (`Flight_id`,`State_id`),
  KEY `Flight_State_ibfk_2` (`State_id`),
  CONSTRAINT `Flight_State_ibfk_1` FOREIGN KEY (`Flight_id`) REFERENCES `Flight` (`Flight_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Flight_State_ibfk_2` FOREIGN KEY (`State_id`) REFERENCES `State` (`State_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of Flight_State
-- ----------------------------
BEGIN;
INSERT INTO `Flight_State` VALUES ('2', '1');
INSERT INTO `Flight_State` VALUES ('1', '2');
INSERT INTO `Flight_State` VALUES ('2', '2');
INSERT INTO `Flight_State` VALUES ('3', '3');
INSERT INTO `Flight_State` VALUES ('4', '6');
INSERT INTO `Flight_State` VALUES ('5', '6');
COMMIT;

-- ----------------------------
-- Table structure for Flight_Ticket
-- ----------------------------
DROP TABLE IF EXISTS `Flight_Ticket`;
CREATE TABLE `Flight_Ticket` (
  `Flight_id` varchar(40) NOT NULL,
  `Ticket_id` varchar(40) NOT NULL,
  PRIMARY KEY (`Flight_id`,`Ticket_id`),
  KEY `Flight_Ticket_ibfk_2` (`Ticket_id`),
  CONSTRAINT `Flight_Ticket_ibfk_1` FOREIGN KEY (`Flight_id`) REFERENCES `Flight` (`Flight_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Flight_Ticket_ibfk_2` FOREIGN KEY (`Ticket_id`) REFERENCES `Ticket` (`Ticket_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of Flight_Ticket
-- ----------------------------
BEGIN;
INSERT INTO `Flight_Ticket` VALUES ('1', '1');
INSERT INTO `Flight_Ticket` VALUES ('1', '12');
INSERT INTO `Flight_Ticket` VALUES ('4', '120');
INSERT INTO `Flight_Ticket` VALUES ('4', '121');
INSERT INTO `Flight_Ticket` VALUES ('4', '122');
INSERT INTO `Flight_Ticket` VALUES ('1', '123');
INSERT INTO `Flight_Ticket` VALUES ('2', '130');
INSERT INTO `Flight_Ticket` VALUES ('1', '18');
INSERT INTO `Flight_Ticket` VALUES ('2', '31');
INSERT INTO `Flight_Ticket` VALUES ('3', '44');
INSERT INTO `Flight_Ticket` VALUES ('3', '52');
COMMIT;

-- ----------------------------
-- Table structure for Operation Log
-- ----------------------------
DROP TABLE IF EXISTS `Operation Log`;
CREATE TABLE `Operation Log` (
  `id` int(11) NOT NULL,
  `Operator_id` varchar(40) NOT NULL,
  `Operation_content` varchar(40) NOT NULL,
  `Operation_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `Operation Log_ibfk_1` (`Operator_id`),
  CONSTRAINT `Operation Log_ibfk_1` FOREIGN KEY (`Operator_id`) REFERENCES `User` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of Operation Log
-- ----------------------------
BEGIN;
INSERT INTO `Operation Log` VALUES (1, '123459', 'Add Tickets', '2020-05-08 12:14:32');
INSERT INTO `Operation Log` VALUES (2, '123459', 'Add Fight——Tickets', '2020-05-08 12:14:32');
COMMIT;

-- ----------------------------
-- Table structure for Role
-- ----------------------------
DROP TABLE IF EXISTS `Role`;
CREATE TABLE `Role` (
  `Role_id` int(11) NOT NULL AUTO_INCREMENT,
  `Role_name` varchar(20) NOT NULL,
  PRIMARY KEY (`Role_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of Role
-- ----------------------------
BEGIN;
INSERT INTO `Role` VALUES (1, '乘客');
INSERT INTO `Role` VALUES (2, '管理员');
INSERT INTO `Role` VALUES (3, '地勤');
COMMIT;

-- ----------------------------
-- Table structure for State
-- ----------------------------
DROP TABLE IF EXISTS `State`;
CREATE TABLE `State` (
  `State_id` varchar(40) NOT NULL,
  `State_name` varchar(40) NOT NULL,
  PRIMARY KEY (`State_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of State
-- ----------------------------
BEGIN;
INSERT INTO `State` VALUES ('1', '准点');
INSERT INTO `State` VALUES ('2', '延误');
INSERT INTO `State` VALUES ('3', '取消');
INSERT INTO `State` VALUES ('4', '飞行中');
INSERT INTO `State` VALUES ('5', '已到达');
INSERT INTO `State` VALUES ('6', '即将起飞');
COMMIT;

-- ----------------------------
-- Table structure for Ticket
-- ----------------------------
DROP TABLE IF EXISTS `Ticket`;
CREATE TABLE `Ticket` (
  `Ticket_id` varchar(40) NOT NULL,
  `Ticket_type` varchar(40) NOT NULL,
  `Ticket_price` decimal(10,2) NOT NULL,
  `Luggage_weight` decimal(10,2) DEFAULT NULL,
  `Seat_number` varchar(40) NOT NULL,
  `ID` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`Ticket_id`),
  KEY `Ticket_ibfk_1` (`ID`),
  CONSTRAINT `Ticket_ibfk_1` FOREIGN KEY (`ID`) REFERENCES `User` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of Ticket
-- ----------------------------
BEGIN;
INSERT INTO `Ticket` VALUES ('1', '经济舱', 100.00, 0.00, '0', '123456');
INSERT INTO `Ticket` VALUES ('12', '商务舱', 200.00, 20.00, '2', '123457');
INSERT INTO `Ticket` VALUES ('120', '经济舱', 1000.00, NULL, '1', NULL);
INSERT INTO `Ticket` VALUES ('121', '头等舱', 2000.00, NULL, '2', NULL);
INSERT INTO `Ticket` VALUES ('122', '商务仓', 100000.00, NULL, '3', NULL);
INSERT INTO `Ticket` VALUES ('123', '商务舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('124', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('125', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('126', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('127', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('128', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('129', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('130', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `Ticket` VALUES ('18', '经济舱', 100.00, NULL, '1', NULL);
INSERT INTO `Ticket` VALUES ('31', '头等舱', 400.00, NULL, '-1', NULL);
INSERT INTO `Ticket` VALUES ('44', '商务舱', 200.00, NULL, '-3', '123454');
INSERT INTO `Ticket` VALUES ('52', '头等舱', 400.00, 0.00, '7', '123454');
COMMIT;

-- ----------------------------
-- Table structure for User
-- ----------------------------
DROP TABLE IF EXISTS `User`;
CREATE TABLE `User` (
  `ID` varchar(40) NOT NULL,
  `Name` varchar(20) NOT NULL,
  `Phone Number` varchar(20) NOT NULL,
  `Nationality` varchar(20) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of User
-- ----------------------------
BEGIN;
INSERT INTO `User` VALUES ('123454', '陈荣', '54749119', '中国');
INSERT INTO `User` VALUES ('123456', '王兆国', '54749110', '中国');
INSERT INTO `User` VALUES ('123457', '臧斌与', '54749120', '中国');
INSERT INTO `User` VALUES ('123458', 'Trump', '111111', '美国');
INSERT INTO `User` VALUES ('123459', '安倍晋三', '222222', '日本');
COMMIT;

-- ----------------------------
-- Table structure for User_Account
-- ----------------------------
DROP TABLE IF EXISTS `User_Account`;
CREATE TABLE `User_Account` (
  `ID` varchar(255) NOT NULL,
  `Account_id` varchar(255) NOT NULL,
  PRIMARY KEY (`ID`,`Account_id`),
  KEY `User_Account_ibfk_2` (`Account_id`),
  CONSTRAINT `User_Account_ibfk_1` FOREIGN KEY (`ID`) REFERENCES `User` (`ID`),
  CONSTRAINT `User_Account_ibfk_2` FOREIGN KEY (`Account_id`) REFERENCES `Account` (`Account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of User_Account
-- ----------------------------
BEGIN;
INSERT INTO `User_Account` VALUES ('123456', '1234567');
INSERT INTO `User_Account` VALUES ('123454', '1234568');
INSERT INTO `User_Account` VALUES ('123457', '1234569');
COMMIT;

-- ----------------------------
-- Table structure for User_Role
-- ----------------------------
DROP TABLE IF EXISTS `User_Role`;
CREATE TABLE `User_Role` (
  `ID` varchar(40) NOT NULL,
  `Role_id` int(11) NOT NULL,
  PRIMARY KEY (`Role_id`,`ID`),
  KEY `User_Role_ibfk_2` (`ID`),
  CONSTRAINT `User_Role_ibfk_1` FOREIGN KEY (`Role_id`) REFERENCES `Role` (`Role_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `User_Role_ibfk_2` FOREIGN KEY (`ID`) REFERENCES `User` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of User_Role
-- ----------------------------
BEGIN;
INSERT INTO `User_Role` VALUES ('123454', 1);
INSERT INTO `User_Role` VALUES ('123456', 1);
INSERT INTO `User_Role` VALUES ('123457', 1);
INSERT INTO `User_Role` VALUES ('123458', 3);
INSERT INTO `User_Role` VALUES ('123459', 2);
COMMIT;

-- ----------------------------
-- Procedure structure for ADD_flight
-- ----------------------------
DROP PROCEDURE IF EXISTS `ADD_flight`;
delimiter ;;
CREATE PROCEDURE `ADD_flight`(IN ID VARCHAR(40),IN start_city VARCHAR(40),IN dest_city VARCHAR(40) ,IN start_date datetime(6),IN dest_date datetime(6))
BEGIN
	DECLARE m VARCHAR(40);
	DECLARE identity INT ;
		SELECT count(*) INTO identity
		FROM (`User` NATURAL JOIN `User_Role`)NATURAL JOIN `Role`
		WHERE `User`.`ID`=ID and `Role_id`= 2 ;
		IF identity>=1 
 		THEN	
	SELECT max(cast(`Flight_id` AS UNSIGNED)) INTO m FROM `Flight`;
	INSERT INTO `Flight` VALUES(m+1,start_city,dest_city,NULL,start_date,dest_date ,NULL,NULL);
	CALL insert_record('Add_Flight',ID);
	INSERT INTO `Flight_State` VALUES(m+1,'6');
	CALL insert_record('Add Flight_State',ID);
	END IF;
	END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for add_tickets
-- ----------------------------
DROP PROCEDURE IF EXISTS `add_tickets`;
delimiter ;;
CREATE PROCEDURE `add_tickets`(IN ID VARCHAR(40), IN flight_num VARCHAR(40),IN seat_num VARCHAR(40),IN type VARCHAR(40),IN price DECIMAL(10,2))
BEGIN
	DECLARE m VARCHAR(40);
	DECLARE identity INT ;
		SELECT count(*) INTO identity
		FROM (`User` NATURAL JOIN `User_Role`)NATURAL JOIN `Role`
		WHERE `User`.`ID`=ID and `Role_id`=2;
		IF identity>=1  AND seat_num NOT IN (SELECT `Seat_number`
                     	FROM (SELECT * FROM `Flight_Ticket` WHERE `Flight_id`=flight_num) AS F NATURAL JOIN  `Ticket`  )	
 		THEN	
		SELECT max(cast(`Ticket_id` AS UNSIGNED)) INTO m FROM `Ticket`;
		INSERT INTO `Ticket` VALUES(m+1,type,price,NULL,seat_num,NULL);
		CALL insert_record('Add ticket',ID);
		INSERT INTO `Flight_Ticket` VALUES (flight_num,m+1);
		CALL insert_record('Add Flight_Ticket',ID);
		END IF;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for buy_ticket
-- ----------------------------
DROP PROCEDURE IF EXISTS `buy_ticket`;
delimiter ;;
CREATE PROCEDURE `buy_ticket`(in id VARCHAR(40),flight_num varchar(40),ticket_tpye VARCHAR(40),seat_number varchar(40))
BEGIN 
    DECLARE fare decimal(10,2);
  DECLARE account_number varchar(40);
  
  SELECT `Ticket_price` into fare
  from `Ticket`
  where (`Ticket_id` in (SELECT `Ticket_id` from `Flight_Ticket` WHERE `Flight_id` = flight_num)) and (`Seat_number` = seat_number) and (`Ticket_type` = ticket_tpye);
  
  SELECT `Account_id` into account_number
  from `User_Account`
  where (id = `ID`);
  
   UPDATE `Ticket`
  set `ID` = id
  where (`Ticket_id` in (SELECT `Ticket_id` from `Flight_Ticket` WHERE `Flight_id` = flight_num)) and (`Seat_number` = seat_number) and (`Ticket_type` = ticket_tpye);
  CALL insert_record('Buy Ticket',id);
	
  UPDATE `Account`
  set `Account_balance` = `Account_balance` - fare
  where (`Account_id` = account_number);
	CALL insert_record('Buy_Update_Account',id);
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for check_flight
-- ----------------------------
DROP PROCEDURE IF EXISTS `check_flight`;
delimiter ;;
CREATE PROCEDURE `check_flight`(IN ID VARCHAR(40))
BEGIN
		DECLARE identity INT ;
		SELECT count(*) INTO identity
		FROM (`User` NATURAL JOIN `User_Role`)NATURAL JOIN `Role`
		WHERE `User`.`ID`=ID and `Role_id`=1 ;
		IF identity>=1 
		THEN
			SELECT `Flight_id`,`Scheduled_departure_time`,`Scheduled_arriving_time`,`Departure_city`,`Scheduled_arriving_city`,`Ticket_type`,`Ticket_price`
			FROM ((SELECT * FROM `Ticket` WHERE `ID`=ID) AS P NATURAL JOIN `Flight_Ticket`)NATURAL JOIN `Flight`;
		END IF;
		CALL insert_record('Find history flight',ID);
	END
;;
delimiter ;

-- ----------------------------
-- Function structure for check_ticket
-- ----------------------------
DROP FUNCTION IF EXISTS `check_ticket`;
delimiter ;;
CREATE FUNCTION `check_ticket`(op_id VARCHAR(40),id VARCHAR(40),ticket_id VARCHAR(40))
 RETURNS int(11)
  DETERMINISTIC
BEGIN  
    DECLARE p_id VARCHAR(40);  
  DECLARE identity VARCHAR(40) ;
  
SELECT count(*) INTO identity
		FROM (`User` NATURAL JOIN `User_Role`)NATURAL JOIN `Role`
		WHERE `role`.`ID`= op_id and `Role_id`=3;
		IF identity>=1 
   THEN
  
      SELECT `ID`  into p_id   
      from  `Ticket`
      WHERE `Ticket_id` = ticket_id;   
     
      if (p_id = id) THEN 
      return 1;
      end if; 
    return 0;
  end if;
  return -1;
	CALL insert_record('check_ticket',id);
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for find_flight
-- ----------------------------
DROP PROCEDURE IF EXISTS `find_flight`;
delimiter ;;
CREATE PROCEDURE `find_flight`(IN ID VARCHAR(40),in startplace VARCHAR(40),destination VARCHAR(40),de_date Date)
BEGIN  
    SELECT `Flight_id`,`Departure_city`,`Scheduled_arriving_city`,`Scheduled_departure_time`,`Scheduled_arriving_time`,`Ticket_type`,`Ticket_price`,`Seat_number`
    FROM  (`Flight`  NATURAL JOIN `Flight_Ticket`) NATURAL JOIN `Ticket`
    WHERE (Date(`Scheduled_departure_time`) = de_date) and (`Departure_city` = startplace) and (`Scheduled_arriving_city` = destination) and (isNULL(`ID`));
		
		CALL insert_record('Find_flight',ID);
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for flight_state
-- ----------------------------
DROP PROCEDURE IF EXISTS `flight_state`;
delimiter ;;
CREATE PROCEDURE `flight_state`(IN ID VARCHAR(40),IN num VARCHAR(40) ,IN state_id VARCHAR(40))
BEGIN
 		DECLARE identity INT ;
		DECLARE done INT DEFAULT 0;
		DECLARE U VARCHAR(255);
		DECLARE price DECIMAL(10,2);
		DECLARE flight_num INT;
		DECLARE cur CURSOR FOR (SELECT  `Account_id`,`Ticket_price` FROM ((((`Flight_Ticket` NATURAL JOIN `Ticket`) NATURAL JOIN `User`) NATURAL JOIN `User_Account`) NATURAL JOIN `Account`) 
					WHERE `Flight_id`=num);
		DECLARE CONTINUE HANDLER FOR NOT FOUND SET done=1; 
 		SELECT count(*) INTO identity
		FROM (`User` NATURAL JOIN `User_Role`)NATURAL JOIN `Role`
		WHERE `User`.`ID`= op_id and `Role_id`=2;
		IF identity>=1 
 		THEN
			
			
			SELECT COUNT(*) INTO flight_num
			FROM `Flight_State`
			WHERE `Flight_id`=num;
			IF flight_num=0
			THEN 
 			INSERT INTO `Flight_State`VALUES (num,state_id);
			CALL insert_record('Add Flight_State',ID);
			ELSE 
			UPDATE `Flight_State` SET `State_id`=state_id WHERE `Flight_id`=num;
			CALL insert_record('Update Flight_State',ID);
			END IF;
			
			OPEN cur ;
			posLoop : LOOP
				
				FETCH cur INTO U,price;
		 			 IF done=1 THEN LEAVE posLoop; END IF;
						IF state_id='2' THEN
					    UPDATE  `Account` SET `Account_balance`=`Account_balance`+price*0.5 WHERE `Account_id`=U;
							CALL insert_record('Flight_Delayed_Refund',ID);
						
						ELSEIF state_id='3' THEN
							UPDATE  `Account` SET `Account_balance`=`Account_balance`+price WHERE `Account_id`=U;
							CALL insert_record('Flight_Cancelled_Refund',ID);
						END IF;
			END LOOP posLoop;			
			CLOSE cur;
		END IF;
	 	END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for insert_record
-- ----------------------------
DROP PROCEDURE IF EXISTS `insert_record`;
delimiter ;;
CREATE PROCEDURE `insert_record`(IN content VARCHAR(40), IN ident VARCHAR(40))
BEGIN
  DECLARE id_num INT(40) DEFAULT 0;
 DECLARE time datetime DEFAULT NOW();
 
  SELECT max(`id`) INTO id_num
	
  FROM `Operation Log`;
	IF ISNULL(id_num) THEN
	SELECT 0 INTO id_num;
	END IF;
 INSERT INTO `Operation Log` VALUES (id_num+1, ident, content, time);
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for record_weight
-- ----------------------------
DROP PROCEDURE IF EXISTS `record_weight`;
delimiter ;;
CREATE PROCEDURE `record_weight`(IN op_id VARCHAR(40),id VARCHAR(40),weight decimal(10,2))
BEGIN  
    DECLARE identity VARCHAR(40) ;

   SELECT count(*) INTO identity
   FROM (`User` NATURAL JOIN `User_Role`)NATURAL JOIN `Role`
   WHERE `User`.`ID`= op_id and `Role_id`=3;
   IF identity>=1 
   THEN
     UPDATE `Ticket`
     set `Luggage_weight` = weight
     where (`Ticket_id` = id) ;
   end if; 
	 CALL insert_record('Add_Luggage_weight',ID); 
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
