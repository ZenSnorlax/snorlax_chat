#include <mysql-cppconn/mysqlx/xdevapi.h>

#include <exception>
#include <iostream>

int main() {
    // 数据库连接信息
    const std::string host = "localhost";      
    const std::string user = "abs";            
    const std::string password = "1510017673"; 
    const std::string dbName = "snorlax_chat";  

    try {
        // 创建 MySQL 客户端会话
        mysqlx::Session session(host, 33060, user, password);

        // 选择数据库
        session.sql("USE " + dbName).execute();

        // 插入数据
        // 修改插入语句以适应新表结构
        session
            .sql(
                "INSERT INTO snorlax_user (account, password) VALUES "
                "('test_user', 'test_pass')")
            .execute();

        // 查询数据
        mysqlx::RowResult result =
            session.sql("SELECT * FROM snorlax_user").execute();

        // 输出查询结果
        std::cout << "Users in the database:" << std::endl;
        for (mysqlx::Row row : result) {
            std::cout << "ID: " << row[0] << ", Account: " << row[1]
                      << std::endl;
        }

        // 关闭会话
        session.close();

    } catch (const mysqlx::Error &err) {
        std::cerr << "Error: " << err.what() << std::endl;
    } catch (std::exception &ex) {
        std::cerr << "STD Exception: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error!" << std::endl;
    }
    try {
        // 创建 MySQL 客户端会话
        mysqlx::Session session(host, 33060, user, password);

        // 选择数据库
        session.sql("USE " + dbName).execute();

        // 插入数据
        session
            .sql(
                "INSERT INTO snorlax_msg (sender, content) VALUES "
                "('test_user', 'Hello, World!')")
            .execute();

        // 查询数据
        mysqlx::RowResult result =
            session.sql("SELECT * FROM snorlax_msg").execute();

        // 输出查询结果
        std::cout << "Messages in the database:" << std::endl;
        for (mysqlx::Row row : result) {
            std::cout << "ID: " << row[0] << ", Sender: " << row[1]
                      << ", Content: " << row[2] << std::endl;
        }

        // 关闭会话
        session.close();

    } catch (const mysqlx::Error &err) {
        std::cerr << "Error: " << err.what() << std::endl;
    } catch (std::exception &ex) {
        std::cerr << "STD Exception: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error!" << std::endl;
    }
    return 0;
}
