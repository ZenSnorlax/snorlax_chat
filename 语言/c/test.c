#include <mysql/mysql.h>
#include <stdio.h>

int main() {
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *server = "localhost";
  char *user = "root";
  char *password = "2423167309-Zzq"; // 替换为您的MySQL密码
  char *database = "database_name";  // 替换为您的数据库名

  // 初始化MySQL客户端库
  mysql_library_init(0, NULL, NULL);

  // 连接到MySQL服务器
  conn = mysql_init(NULL);
  if (conn == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
  }

  if (!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  // 创建数据库
  if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS ctest")) {
    fprintf(stderr, "Error creating database: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  // 选择数据库
  mysql_select_db(conn, database);

  // 创建表
  if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS ctest.users (id INT "
                        "AUTO_INCREMENT PRIMARY KEY, name VARCHAR(50))")) {
    fprintf(stderr, "Error creating table: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  // 插入数据
  if (mysql_query(conn, "INSERT INTO ctest.users (name) VALUES ('John Doe')")) {
    fprintf(stderr, "Error inserting data: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  // 查询数据
  if (mysql_query(conn, "SELECT * FROM ctest.users")) {
    fprintf(stderr, "Error querying data: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  // 获取查询结果
  res = mysql_store_result(conn);

  // 遍历结果集
  while ((row = mysql_fetch_row(res))) {
    printf("ID: %s, Name: %s\n", row[0], row[1]);
  }

  // 释放结果集
  mysql_free_result(res);

  // 关闭MySQL连接
  mysql_close(conn);

  // 清理MySQL客户端库
  mysql_library_end();

  return 0;
}
