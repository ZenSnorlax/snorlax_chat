#include <mysql-cppconn/mysqlx/xdevapi.h>

#include <condition_variable>
#include <cstddef>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "../snorlax_log.hpp"

struct SQLConfig {
    std::string host;
    std::string user;
    int port;
    std::string password;
    std::string db_name;
};

class SQLConnPool {
   public:
    static SQLConnPool& getInstance(SQLConfig&& config, size_t size = 10) {
        static SQLConnPool conn_pool(std::move(config), size);
        return conn_pool;
    }

    std::unique_ptr<mysqlx::Session> getConnection() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !queue_.empty(); });
        auto session = std::move(queue_.front());
        queue_.pop();

        LOG(Level::DEBUG,
            "thread ",
            std::this_thread::get_id(),
            " attain a connection");
        return session;
    }

    void releaseConnection(std::unique_ptr<mysqlx::Session> session) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(session));
        LOG(Level::DEBUG,
            "thread ",
            std::this_thread::get_id(),
            " release a connection");
        cv_.notify_one();
    }

    void resize(size_t newSize) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (newSize > capacity) {
            while (capacity < newSize) {
                queue_.push(createSession());
                capacity++;
            }
        } else if (newSize < capacity) {
            while (capacity > newSize && !queue_.empty()) {
                queue_.pop();
                capacity--;
            }
        }
        LOG(Level::DEBUG, "reset connectionpool capacity");
    }

    SQLConnPool(const SQLConnPool&) = delete;
    SQLConnPool& operator=(const SQLConnPool&) = delete;
    SQLConnPool(SQLConnPool&&) = delete;
    SQLConnPool& operator=(SQLConnPool&&) = delete;

   private:
    SQLConnPool(SQLConfig&& config, size_t size)
        : config_(config), capacity(size) {
        for (size_t i = 0; i < size; ++i) {
            queue_.push(createSession());
        }
        LOG(Level::DEBUG, "create SQLConnPool");
    }

    ~SQLConnPool() {
        std::lock_guard<std::mutex> lock(mutex_);
        LOG(Level::DEBUG, "delete SQLConnPool");
    }

    std::unique_ptr<mysqlx::Session> createSession() {
        return std::make_unique<mysqlx::Session>(
            config_.host, config_.port, config_.user, config_.password);
    }

    SQLConfig config_;
    std::queue<std::unique_ptr<mysqlx::Session>> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    size_t capacity;
};
