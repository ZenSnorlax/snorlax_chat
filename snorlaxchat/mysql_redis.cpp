#include <iostream>
#include <memory>

#ifdef USE_MYSQL
#include <mysql-cppconn-8/mysqlx/xdevapi.h>
#endif

#ifdef USE_REDIS
#include <sw/redis++/redis++.h>
#endif

constexpr char host[] = "127.0.0.1";
constexpr char user[] = "abs";
constexpr int port = 33060; // MySQL X Protocol 默认端口
constexpr char password[] = "1510017673";
constexpr char database[] = "my_database";

#ifdef USE_MYSQL
class Mysql {
  public:
    Mysql(const std::string &host, const std::string &user, int port,
          const std::string &password, const std::string &database)
        : session(mysqlx::SessionSettings(host, port, user, password)) {
        try {
            session.sql("USE " + database).execute();
            std::cout << "Connected to MySQL successfully!" << std::endl;
        } catch (const mysqlx::Error &e) {
            throw std::runtime_error("Error selecting database: " +
                                     std::string(e.what()));
        }
    }

    void dropTable(const std::string &tableName) {
        try {
            session.sql("DROP TABLE " + tableName).execute();
            std::cout << "Dropped table: " << tableName << std::endl;
        } catch (const mysqlx::Error &e) {
            throw std::runtime_error("Error dropping table: " +
                                     std::string(e.what()));
        }
    }

    void createTable(const std::string &tableName) {
        try {
            session
                .sql("CREATE TABLE " + tableName +
                     " (id INT PRIMARY KEY, name VARCHAR(255), age INT)")
                .execute();
            std::cout << "Created table: " << tableName << std::endl;
        } catch (const mysqlx::Error &e) {
            throw std::runtime_error("Error creating table: " +
                                     std::string(e.what()));
        }
    }

    void insertData(const std::string &tableName, int id,
                    const std::string &name, int age) {
        try {
            session
                .sql("INSERT INTO " + tableName +
                     " (id, name, age) VALUES (?, ?, ?)")
                .bind(id, name, age)
                .execute();
            std::cout << "Inserted data into table: " << tableName << std::endl;
        } catch (const mysqlx::Error &e) {
            throw std::runtime_error("Error inserting data: " +
                                     std::string(e.what()));
        }
    }

    void selectData(const std::string &tableName) {
        try {
            mysqlx::SqlResult result =
                session.sql("SELECT * FROM " + tableName).execute();
            std::cout << "Selecting data from table: " << tableName
                      << std::endl;

            for (auto row : result) {
                int id = row[0].get<int>();
                std::string name = row[1].get<std::string>();
                int age = row[2].get<int>();

                std::cout << "ID: " << id << ", Name: " << name
                          << ", Age: " << age << std::endl;
            }
        } catch (const mysqlx::Error &e) {
            throw std::runtime_error("Error selecting data: " +
                                     std::string(e.what()));
        }
    }

    void updateData(const std::string &tableName, int id,
                    const std::string &name, int age) {
        try {
            session
                .sql("UPDATE " + tableName +
                     " SET name = ?, age = ? WHERE id = ?")
                .bind(name, age, id)
                .execute();
            std::cout << "Updated data in table: " << tableName << std::endl;
        } catch (const mysqlx::Error &e) {
            throw std::runtime_error("Error updating data: " +
                                     std::string(e.what()));
        }
    }

    ~Mysql() { session.close(); }

  private:
    mysqlx::Session session;
};
#endif

#ifdef USE_REDIS
class Redis {
  public:
    Redis(const std::string &url) : redis(url) {}

    void setHash(const std::string &key, const std::string &field,
                 const std::string &value) {
        redis.hset(key, field, value);
    }

    std::optional<std::string> getField(const std::string &key,
                                        const std::string &field) {
        return redis.hget(key, field);
    }

    void deleteField(const std::string &key, const std::string &field) {
        redis.hdel(key, field);
    }

    std::unordered_map<std::string, std::string>
    getHash(const std::string &key) {
        std::unordered_map<std::string, std::string> result;
        redis.hgetall(key, std::inserter(result, result.begin()));
        return result;
    }

  private:
    sw::redis::Redis redis;
};
#endif

int main(int argc, char *argv[]) {
#ifdef USE_MYSQL
    try {
        auto session =
            std::make_unique<Mysql>(host, user, port, password, database);

        session->createTable("my_table");
        session->insertData("my_table", 1, "John", 25);
        session->insertData("my_table", 2, "Jane", 30);
        session->insertData("my_table", 3, "Bob", 40);
        session->selectData("my_table");
        session->updateData("my_table", 2, "Alice", 35);
        session->dropTable("my_table");

        std::cout << "Done!" << std::endl;
    } catch (const mysqlx::Error &e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    } catch (const std::runtime_error &e) {
        std::cerr << "MySQL error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
        return 1;
    }
#endif

#ifdef USE_REDIS
    try {
        Redis redis("redis://127.0.0.1:6379");
        redis.setHash("my_hash", "field1", "value1");
        redis.setHash("my_hash", "field2", "value2");
        redis.setHash("my_hash", "field3", "value3");

        std::unordered_map<std::string, std::string> result =
            redis.getHash("my_hash");
        for (const auto &pair : result) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }

        std::optional<std::string> value = redis.getField("my_hash", "field2");
        if (value) {
            std::cout << "field2: " << *value << std::endl;
        } else {
            std::cout << "Field2 not found." << std::endl;
        }

        for (const auto &pair : result) {
            redis.deleteField("my_hash", pair.first);
        }

    } catch (const std::exception &e) {
        std::cerr << "Redis error: " << e.what() << std::endl;
        return 1;
    }
#endif
    return 0;
}
