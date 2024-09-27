SET NAMES utf8;

DROP TABLE IF EXISTS snorlax_user;
CREATE TABLE snorlax_user (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `account` CHAR(14) NOT NULL,
  `password` VARCHAR(255) NOT NULL, -- 调整长度以适应哈希密码
  `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- 创建时间
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS snorlax_chatroom;
CREATE TABLE snorlax_chatroom (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(255) NOT NULL, -- 聊天室名称
  `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- 创建时间
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS snorlax_user_chatroom;
CREATE TABLE snorlax_user_chatroom (
  `user_id` INT(11) NOT NULL,
  `chatroom_id` INT(11) NOT NULL,
  PRIMARY KEY (`user_id`, `chatroom_id`),
  FOREIGN KEY (`user_id`) REFERENCES snorlax_user(`id`) ON DELETE CASCADE,
  FOREIGN KEY (`chatroom_id`) REFERENCES snorlax_chatroom(`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
