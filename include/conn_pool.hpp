#include <mysql-cppconn/mysqlx/xdevapi.h>

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

#include "snorlax_log.hpp"

class ConnectionPool {
   public:
    static ConnectionPool &getInstance() {
        static ConnectionPool pool;
        return pool;
    }

    // Initialize the pool with a given capacity
    void Intialize(std::size_t capacity, std::string host, int port,
                   std::string user, std::string passwd) {
        capacity_ = capacity;

        for (size_t i = 0; i < capacity_; ++i) {
            queue_.emplace(new mysqlx::Session(host, port, user, passwd));
        }
        LOG(Level::INFO, "Initialize connection pool successfully");
    }

    // Get a connection from the pool
    mysqlx::Session *getConnection() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !queue_.empty(); });

        mysqlx::Session *conn = queue_.front();
        queue_.pop();

        LOG(Level::INFO,
            std::this_thread::get_id(),
            " Get a connection from the pool");

        return conn;
    }

    // Release a connection back to the pool
    void releaseConnection(mysqlx::Session *conn) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(conn);
        }

        LOG(Level::INFO,
            std::this_thread::get_id(),
            " Release a connection back to the pool");

        cv_.notify_one();
    }

    // Get the capacity of the pool
    std::size_t getCapacity() { return capacity_; }

   private:
    std::size_t capacity_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<mysqlx::Session *> queue_;

    ConnectionPool() { capacity_ = 0; }

    // Destructor of the pool
    ~ConnectionPool() {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!queue_.empty()) {
            delete queue_.front();
            queue_.pop();
        }

        LOG(Level::INFO, "Destroy connection pool successfully");
    }
};

class ConnectionGuard {
   public:
    explicit ConnectionGuard(mysqlx::Session *conn) : conn_(conn) {
        conn_->startTransaction();
    }

    ~ConnectionGuard() {
        conn_->commit();
        ConnectionPool::getInstance().releaseConnection(conn_);
    }

    // Get the underlying connection
    mysqlx::Session *operator->() { return conn_; }
    mysqlx::Session &operator*() { return *conn_; }

   private:
    mysqlx::Session *conn_;
};