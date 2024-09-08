-- 创建数据库
CREATE DATABASE IF NOT EXISTS my_database;

-- 切换到新创建的数据库
USE my_database;

-- 创建表
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_name VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);

-- 可以添加更多表和初始化数据的 SQL 语句
