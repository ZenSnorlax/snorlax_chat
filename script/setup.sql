-- disable foreign key
SET FOREIGN_KEY_CHECKS=0;
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS user_room_relations;
DROP TABLE IF EXISTS messages;
DROP TABLE IF EXISTS chat_rooms;
-- enable foreign key
SET FOREIGN_KEY_CHECKS=1;

-- create users table
CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    last_login TIMESTAMP,
    status ENUM('active', 'inactive') DEFAULT 'active'
);

-- create chat_rooms table,set cascade
CREATE TABLE chat_rooms (
    id INT PRIMARY KEY AUTO_INCREMENT,
    room_name VARCHAR(100) UNIQUE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    created_by INT NOT NULL,
    FOREIGN KEY (created_by) REFERENCES users(id) ON DELETE CASCADE
);

-- create messages table, set cascade
CREATE TABLE messages (
    id INT PRIMARY KEY AUTO_INCREMENT,
    room_id INT NOT NULL,
    user_id INT NOT NULL,
    content TEXT NOT NULL,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (room_id) REFERENCES chat_rooms(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

-- create user_room_relations table, set cascade
CREATE TABLE user_room_relations (
    user_id INT NOT NULL,
    room_id INT NOT NULL,
    joined_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    role ENUM('admin', 'member') DEFAULT 'member',
    PRIMARY KEY (user_id, room_id),
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (room_id) REFERENCES chat_rooms(id) ON DELETE CASCADE
);
