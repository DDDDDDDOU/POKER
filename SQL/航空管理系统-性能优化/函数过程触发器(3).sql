/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 50710
 Source Host           : localhost:3306
 Source Schema         : `Aviation management system`

 Target Server Type    : MySQL
 Target Server Version : 50710
 File Encoding         : 65001

 Date: 08/05/2020 12:32:03
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

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
