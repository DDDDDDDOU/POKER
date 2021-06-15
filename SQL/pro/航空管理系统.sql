/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 50710
 Source Host           : localhost:3306
 Source Schema         : 航空管理系统

 Target Server Type    : MySQL
 Target Server Version : 50710
 File Encoding         : 65001

 Date: 08/05/2020 12:32:03
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for 操作记录
-- ----------------------------
DROP TABLE IF EXISTS `操作记录`;
CREATE TABLE `操作记录` (
  `id` int(11) NOT NULL,
  `操作人id` varchar(40) NOT NULL,
  `操作内容` varchar(40) NOT NULL,
  `操作时间` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `操作人id` (`操作人id`),
  CONSTRAINT `操作记录_ibfk_1` FOREIGN KEY (`操作人id`) REFERENCES `用户` (`身份证号码`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 操作记录
-- ----------------------------
BEGIN;
INSERT INTO `操作记录` VALUES (1, '123459', '添加机票', '2020-05-08 12:14:32');
INSERT INTO `操作记录` VALUES (2, '123459', '添加航班——机票', '2020-05-08 12:14:32');
COMMIT;

-- ----------------------------
-- Table structure for 机票
-- ----------------------------
DROP TABLE IF EXISTS `机票`;
CREATE TABLE `机票` (
  `机票编号` varchar(40) NOT NULL,
  `机票种类` varchar(40) NOT NULL,
  `票价` decimal(10,2) NOT NULL,
  `行李重量` decimal(10,2) DEFAULT NULL,
  `座位号` varchar(40) NOT NULL,
  `身份证号码` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`机票编号`),
  KEY `乘客身份证编号` (`身份证号码`),
  CONSTRAINT `机票_ibfk_1` FOREIGN KEY (`身份证号码`) REFERENCES `用户` (`身份证号码`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 机票
-- ----------------------------
BEGIN;
INSERT INTO `机票` VALUES ('1', '经济舱', 100.00, 0.00, '0', '123456');
INSERT INTO `机票` VALUES ('12', '商务舱', 200.00, 20.00, '2', '123457');
INSERT INTO `机票` VALUES ('120', '经济舱', 1000.00, NULL, '1', NULL);
INSERT INTO `机票` VALUES ('121', '头等舱', 2000.00, NULL, '2', NULL);
INSERT INTO `机票` VALUES ('122', '商务仓', 100000.00, NULL, '3', NULL);
INSERT INTO `机票` VALUES ('123', '商务舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('124', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('125', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('126', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('127', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('128', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('129', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('130', '经济舱', 1000.00, NULL, '10', NULL);
INSERT INTO `机票` VALUES ('18', '经济舱', 100.00, NULL, '1', NULL);
INSERT INTO `机票` VALUES ('31', '头等舱', 400.00, NULL, '-1', NULL);
INSERT INTO `机票` VALUES ('44', '商务舱', 200.00, NULL, '-3', '123454');
INSERT INTO `机票` VALUES ('52', '头等舱', 400.00, 0.00, '7', '123454');
COMMIT;

-- ----------------------------
-- Table structure for 状态
-- ----------------------------
DROP TABLE IF EXISTS `状态`;
CREATE TABLE `状态` (
  `状态编号` varchar(40) NOT NULL,
  `状态名称` varchar(40) NOT NULL,
  PRIMARY KEY (`状态编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 状态
-- ----------------------------
BEGIN;
INSERT INTO `状态` VALUES ('1', '准点');
INSERT INTO `状态` VALUES ('2', '延误');
INSERT INTO `状态` VALUES ('3', '取消');
INSERT INTO `状态` VALUES ('4', '飞行中');
INSERT INTO `状态` VALUES ('5', '已到达');
INSERT INTO `状态` VALUES ('6', '即将起飞');
COMMIT;

-- ----------------------------
-- Table structure for 用户
-- ----------------------------
DROP TABLE IF EXISTS `用户`;
CREATE TABLE `用户` (
  `身份证号码` varchar(40) NOT NULL,
  `姓名` varchar(20) NOT NULL,
  `电话号码` varchar(20) NOT NULL,
  `国籍` varchar(20) NOT NULL,
  PRIMARY KEY (`身份证号码`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 用户
-- ----------------------------
BEGIN;
INSERT INTO `用户` VALUES ('123454', '陈荣', '54749119', '中国');
INSERT INTO `用户` VALUES ('123456', '王兆国', '54749110', '中国');
INSERT INTO `用户` VALUES ('123457', '臧斌与', '54749120', '中国');
INSERT INTO `用户` VALUES ('123458', 'Trump', '111111', '美国');
INSERT INTO `用户` VALUES ('123459', '安倍晋三', '222222', '日本');
COMMIT;

-- ----------------------------
-- Table structure for 用户_角色
-- ----------------------------
DROP TABLE IF EXISTS `用户_角色`;
CREATE TABLE `用户_角色` (
  `身份证号码` varchar(40) NOT NULL,
  `角色编号` int(11) NOT NULL,
  PRIMARY KEY (`角色编号`,`身份证号码`),
  KEY `身份证号码` (`身份证号码`),
  CONSTRAINT `用户_角色_ibfk_1` FOREIGN KEY (`角色编号`) REFERENCES `角色` (`角色编号`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `用户_角色_ibfk_2` FOREIGN KEY (`身份证号码`) REFERENCES `用户` (`身份证号码`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 用户_角色
-- ----------------------------
BEGIN;
INSERT INTO `用户_角色` VALUES ('123454', 1);
INSERT INTO `用户_角色` VALUES ('123456', 1);
INSERT INTO `用户_角色` VALUES ('123457', 1);
INSERT INTO `用户_角色` VALUES ('123458', 3);
INSERT INTO `用户_角色` VALUES ('123459', 2);
COMMIT;

-- ----------------------------
-- Table structure for 用户_账户
-- ----------------------------
DROP TABLE IF EXISTS `用户_账户`;
CREATE TABLE `用户_账户` (
  `身份证号码` varchar(255) NOT NULL,
  `账户号码` varchar(255) NOT NULL,
  PRIMARY KEY (`身份证号码`,`账户号码`),
  KEY `用户_账户_ibfk_2` (`账户号码`),
  CONSTRAINT `用户_账户_ibfk_1` FOREIGN KEY (`身份证号码`) REFERENCES `用户` (`身份证号码`),
  CONSTRAINT `用户_账户_ibfk_2` FOREIGN KEY (`账户号码`) REFERENCES `账户` (`账户号码`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 用户_账户
-- ----------------------------
BEGIN;
INSERT INTO `用户_账户` VALUES ('123456', '1234567');
INSERT INTO `用户_账户` VALUES ('123454', '1234568');
INSERT INTO `用户_账户` VALUES ('123457', '1234569');
COMMIT;

-- ----------------------------
-- Table structure for 航班
-- ----------------------------
DROP TABLE IF EXISTS `航班`;
CREATE TABLE `航班` (
  `航班号` varchar(40) NOT NULL,
  `出发城市` varchar(40) NOT NULL,
  `预计到达城市` varchar(40) NOT NULL,
  `实际到达城市` varchar(40) DEFAULT NULL,
  `出发时间` datetime(6) NOT NULL,
  `预计到达时间` datetime(6) NOT NULL,
  `实际到达时间` datetime(6) DEFAULT NULL,
  `实际出发时间` datetime(6) DEFAULT NULL,
  PRIMARY KEY (`航班号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 航班
-- ----------------------------
BEGIN;
INSERT INTO `航班` VALUES ('1', '上海', '北京', NULL, '2020-05-07 10:10:10.000000', '2020-05-07 12:10:10.000000', NULL, NULL);
INSERT INTO `航班` VALUES ('2', '上海', '南京', '南京', '2020-05-07 10:11:11.000000', '2020-05-07 11:10:10.000000', '2020-05-07 11:10:12.000000', '2020-05-07 10:11:00.000000');
INSERT INTO `航班` VALUES ('3', '上海', '东京', NULL, '2020-05-07 10:10:10.000000', '2020-05-07 14:10:10.000000', NULL, NULL);
INSERT INTO `航班` VALUES ('4', '上海', '北京', NULL, '2020-05-07 11:30:20.000000', '2020-05-07 15:00:30.000000', NULL, NULL);
INSERT INTO `航班` VALUES ('5', '上海', '北京', NULL, '2020-05-20 10:00:00.000000', '2020-05-21 10:00:00.000000', NULL, NULL);
COMMIT;

-- ----------------------------
-- Table structure for 航班_机票
-- ----------------------------
DROP TABLE IF EXISTS `航班_机票`;
CREATE TABLE `航班_机票` (
  `航班号` varchar(40) NOT NULL,
  `机票编号` varchar(40) NOT NULL,
  PRIMARY KEY (`航班号`,`机票编号`),
  KEY `机票编号` (`机票编号`),
  CONSTRAINT `航班_机票_ibfk_1` FOREIGN KEY (`航班号`) REFERENCES `航班` (`航班号`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `航班_机票_ibfk_2` FOREIGN KEY (`机票编号`) REFERENCES `机票` (`机票编号`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 航班_机票
-- ----------------------------
BEGIN;
INSERT INTO `航班_机票` VALUES ('1', '1');
INSERT INTO `航班_机票` VALUES ('1', '12');
INSERT INTO `航班_机票` VALUES ('4', '120');
INSERT INTO `航班_机票` VALUES ('4', '121');
INSERT INTO `航班_机票` VALUES ('4', '122');
INSERT INTO `航班_机票` VALUES ('1', '123');
INSERT INTO `航班_机票` VALUES ('2', '130');
INSERT INTO `航班_机票` VALUES ('1', '18');
INSERT INTO `航班_机票` VALUES ('2', '31');
INSERT INTO `航班_机票` VALUES ('3', '44');
INSERT INTO `航班_机票` VALUES ('3', '52');
COMMIT;

-- ----------------------------
-- Table structure for 航班_状态
-- ----------------------------
DROP TABLE IF EXISTS `航班_状态`;
CREATE TABLE `航班_状态` (
  `航班号` varchar(40) NOT NULL,
  `状态编号` varchar(40) NOT NULL,
  PRIMARY KEY (`航班号`,`状态编号`),
  KEY `状态编号` (`状态编号`),
  CONSTRAINT `航班_状态_ibfk_1` FOREIGN KEY (`航班号`) REFERENCES `航班` (`航班号`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `航班_状态_ibfk_2` FOREIGN KEY (`状态编号`) REFERENCES `状态` (`状态编号`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 航班_状态
-- ----------------------------
BEGIN;
INSERT INTO `航班_状态` VALUES ('2', '1');
INSERT INTO `航班_状态` VALUES ('1', '2');
INSERT INTO `航班_状态` VALUES ('2', '2');
INSERT INTO `航班_状态` VALUES ('3', '3');
INSERT INTO `航班_状态` VALUES ('4', '6');
INSERT INTO `航班_状态` VALUES ('5', '6');
COMMIT;

-- ----------------------------
-- Table structure for 角色
-- ----------------------------
DROP TABLE IF EXISTS `角色`;
CREATE TABLE `角色` (
  `角色编号` int(11) NOT NULL AUTO_INCREMENT,
  `角色名` varchar(20) NOT NULL,
  PRIMARY KEY (`角色编号`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 角色
-- ----------------------------
BEGIN;
INSERT INTO `角色` VALUES (1, '乘客');
INSERT INTO `角色` VALUES (2, '管理员');
INSERT INTO `角色` VALUES (3, '地勤');
COMMIT;

-- ----------------------------
-- Table structure for 账户
-- ----------------------------
DROP TABLE IF EXISTS `账户`;
CREATE TABLE `账户` (
  `账户号码` varchar(40) NOT NULL,
  `账户余额` decimal(13,2) NOT NULL,
  PRIMARY KEY (`账户号码`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Procedure structure for ADD_flight
-- ----------------------------
DROP PROCEDURE IF EXISTS `ADD_flight`;
delimiter ;;
CREATE PROCEDURE `ADD_flight`(IN ID VARCHAR(40),IN start_city VARCHAR(40),IN dest_city VARCHAR(40) ,IN start_date datetime(6),IN dest_date datetime(6))
BEGIN
	DECLARE m VARCHAR(40);
	DECLARE identity INT;
	SELECT `角色编号` INTO identity  
 		FROM (`用户` NATURAL JOIN `用户_角色`) NATURAL JOIN `角色`
 		WHERE `用户`.`身份证号码`=ID ;
 		IF identity='2' 
 		THEN	
	SELECT max(cast(`航班号` AS UNSIGNED)) INTO m FROM `航班`;
	INSERT INTO `航班` VALUES(m+1,start_city,dest_city,NULL,start_date,dest_date ,NULL,NULL);
	CALL insert_record('添加航班',ID);
	INSERT INTO `航班_状态`VALUES(m+1,'6');
	CALL insert_record('添加航班_状态',ID);
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
	DECLARE identity INT;
	SELECT `角色编号` INTO identity  
 		FROM (`用户` NATURAL JOIN `用户_角色`) NATURAL JOIN `角色`
 		WHERE `用户`.`身份证号码`=ID ;
 		IF identity='2' AND seat_num NOT IN (SELECT `座位号`
																					FROM (SELECT * FROM `航班_机票` WHERE `航班号`=flight_num) AS F NATURAL JOIN  `机票`
									
																					)
 		THEN	
		SELECT max(cast(`机票编号` AS UNSIGNED)) INTO m FROM `机票`;
		INSERT INTO `机票` VALUES(m+1,type,price,NULL,seat_num,NULL);
		CALL insert_record('添加机票',ID);
		INSERT INTO `航班_机票` VALUES (flight_num,m+1);
		CALL insert_record('添加航班_机票',ID);
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
  
  SELECT `票价` into fare
  from `机票`
  where (`机票编号` in (SELECT `机票编号` from `航班_机票` WHERE `航班号` = flight_num)) and (`座位号` = seat_number) and (`机票种类` = ticket_tpye);
  
  SELECT `账户号码` into account_number
  from `用户_账户`
  where (id = `身份证号码`);
  
   UPDATE `机票`
  set `身份证号码` = id
  where (`机票编号` in (SELECT `机票编号` from `航班_机票` WHERE `航班号` = flight_num)) and (`座位号` = seat_number) and (`机票种类` = ticket_tpye);
  CALL insert_record('购买机票',id);
	
  UPDATE `账户`
  set `账户余额` = `账户余额` - fare
  where (`账户号码` = account_number);
	CALL insert_record('购买_更新账户',id);
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
		SELECT `角色编号` INTO identity
		FROM (`用户` NATURAL JOIN `用户_角色`)NATURAL JOIN `角色`
		WHERE `用户`.`身份证号码`=ID;
		IF identity=1 
		THEN
			SELECT `航班号`,`出发时间`,`预计到达时间`,`出发城市`,`预计到达城市`,`机票种类`,`票价`
			FROM ((SELECT * FROM `机票` WHERE `身份证号码`=ID) AS P NATURAL JOIN `航班_机票`)NATURAL JOIN `航班`;
		END IF;
		CALL insert_record('查询航班',ID);
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
  
  SELECT `角色编号` INTO identity
   FROM `用户` NATURAL JOIN `用户_角色` NATURAL JOIN `角色`
   WHERE `用户`.`身份证号码`= op_id;
   IF identity='3' 
   THEN
  
      SELECT `乘客身份证号`  into p_id   
      from  `机票`
      WHERE `机票编号` = ticket_id;   
     
      if (p_id = id) THEN 
      return 1;
      end if; 
    return 0;
  end if;
  return -1;
	CALL insert_record('检票',id);
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
    SELECT `航班号`,`出发城市`,`预计到达城市`,`出发时间`,`预计到达时间`,`机票种类`,`票价`,`座位号`
    FROM  (`航班`  NATURAL JOIN `航班_机票`) NATURAL JOIN `机票`
    WHERE (Date(`出发时间`) = de_date) and (`出发城市` = startplace) and (`预计到达城市` = destination) and (isNULL(`身份证号码`));
		
		CALL insert_record('查询航班',ID);
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
		DECLARE cur CURSOR FOR (SELECT  `账户号码`,`票价` FROM ((((`航班_机票` NATURAL JOIN `机票`) NATURAL JOIN `用户`) NATURAL JOIN `用户_账户`) NATURAL JOIN `账户`) WHERE `航班号`='1');
		DECLARE CONTINUE HANDLER FOR NOT FOUND SET done=1; 
 		SELECT `角色编号` INTO identity  
 		FROM `用户` NATURAL JOIN `用户_角色` NATURAL JOIN `角色`
 		WHERE `用户`.`身份证号码`=ID ;
 		IF identity='2' 
 		THEN
			
			
			SELECT COUNT(*) INTO flight_num
			FROM `航班_状态`
			WHERE `航班号`=num;
			IF flight_num=0
			THEN 
 			INSERT INTO `航班_状态`VALUES (num,state_id);
			CALL insert_record('添加航班_状态',ID);
			ELSE 
			UPDATE `航班_状态` SET `状态编号`=state_id WHERE `航班号`=num;
			CALL insert_record('更新航班_状态',ID);
			END IF;
			
			OPEN cur ;
			posLoop : LOOP
				
				FETCH cur INTO U,price;
		 			 IF done=1 THEN LEAVE posLoop; END IF;
						IF state_id='2' THEN
					    UPDATE  `账户` SET `账户余额`=`账户余额`+price*0.5 WHERE `账户号码`=U;
							CALL insert_record('航班延误_退款',ID);
						
						ELSEIF state_id='3' THEN
							UPDATE  `账户` SET `账户余额`=`账户余额`+price WHERE `账户号码`=U;
							CALL insert_record('航班取消_退款',ID);
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
	
  FROM `操作记录`;
	IF ISNULL(id_num) THEN
	SELECT 0 INTO id_num;
	END IF;
 INSERT INTO `操作记录` VALUES (id_num+1, ident, content, time);
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

   SELECT `角色编号` INTO identity
   FROM `用户` NATURAL JOIN `用户_角色` NATURAL JOIN `角色`
   WHERE `用户`.`身份证号码`= op_id;
   IF identity='3' 
   THEN
     UPDATE `机票`
     set `行李重量` = weight
     where (`机票编号` = id) ;
   end if; 
	 CALL insert_record('添加行李重量',ID); 
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
