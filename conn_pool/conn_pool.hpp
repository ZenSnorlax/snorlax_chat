#pragma once
#include <mysql-cppconn/mysqlx/xdevapi.h>

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

#include "../log/snorlax_log.hpp"

struct Config {
    std::string host;
    int port;
    std::string user;
    std::string password;
};

class ConnectionPool {
   public:
    static ConnectionPool& getInstance(Config& config, size_t size = 10) {
        static ConnectionPool conn_pool(std::move(config), size);
        return conn_pool;
    }

    std::unique_ptr<mysqlx::Session> getConnection(
        std::chrono::milliseconds timeout = std::chrono::milliseconds(3000),
        int max_retries = 10,
        std::chrono::milliseconds retry_interval =
            std::chrono::milliseconds(1000)) {
        for (int attempt = 0; attempt <= max_retries; ++attempt) {
            auto session = tryGetConnection(timeout, attempt);
            if (session) {
                return std::move(session.value());
            }
            std::this_thread::sleep_for(retry_interval);
        }
        return nullptr;
    }

    void releaseConnection(std::unique_ptr<mysqlx::Session> session) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(session));
        LOG(Level::DEBUG,
            "Thread ",
            std::this_thread::get_id(),
            " released a connection");
        cv_.notify_one();
    }

    void resize(size_t newSize) {
        std::lock_guard<std::mutex> lock(mutex_);
        while (capacity < newSize) {
            queue_.push(createSession());
            capacity++;
        }
        while (capacity > newSize && !queue_.empty()) {
            queue_.pop();
            capacity--;
        }
        LOG(Level::DEBUG, "Connection pool resized to ", capacity);
    }

   private:
    std::optional<std::unique_ptr<mysqlx::Session>> tryGetConnection(
        std::chrono::milliseconds timeout, int attempt) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (cv_.wait_for(lock, timeout, [this] { return !queue_.empty(); })) {
            auto session = std::move(queue_.front());
            queue_.pop();
            LOG(Level::DEBUG,
                "Thread ",
                std::this_thread::get_id(),
                " got a connection on attempt ",
                attempt + 1);
            return session;
        } else {
            LOG(Level::WARNING,
                "Thread ",
                std::this_thread::get_id(),
                " failed to get a connection on attempt ",
                attempt + 1);
        }
        return std::nullopt;
    }

    ConnectionPool(Config&& config, size_t size)
        : config_(std::move(config)), capacity(size) {
        for (size_t i = 0; i < size; ++i) {
            queue_.push(createSession());
        }
        LOG(Level::DEBUG, "Created ConnectionPool with capacity ", capacity);
    }

    ~ConnectionPool() {
        std::lock_guard<std::mutex> lock(mutex_);
        LOG(Level::DEBUG,
            "Deleting ConnectionPool with ",
            queue_.size(),
            " connections remaining.");
    }

    std::unique_ptr<mysqlx::Session> createSession() {
        return std::make_unique<mysqlx::Session>(
            config_.host, config_.port, config_.user, config_.password);
    }

    Config config_;
    std::queue<std::unique_ptr<mysqlx::Session>> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    size_t capacity;
};
