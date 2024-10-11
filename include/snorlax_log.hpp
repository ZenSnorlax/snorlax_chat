#pragma once
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>

#define LOG(level, ...) \
    SnorlaxLog::getInstance().log(level, __FILE__, __LINE__, __VA_ARGS__)

enum class Level { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class SnorlaxLog {
   public:
    static SnorlaxLog &getInstance() {
        static SnorlaxLog logger;
        return logger;
    }

    void setLevel(Level level) {
        std::lock_guard<std::mutex> lock(mutex_);
        current_level_ = level;
    }

    template <typename... Args>
    void log(Level level, const char *file, int line, Args... args) {
        if (static_cast<int>(level) >= static_cast<int>(current_level_)) {
            std::ostringstream oss;
            oss << "[" << getCurrentTime() << "] "
                << "[" << getLevelName(level) << "] "
                << "[" << file << ":" << line << "] : ";
            (oss << ... << args);

            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(std::move(oss.str()));
                cv_.notify_one();
            }
        }
    }

    void setOutputStream(std::ostream &out) {
        std::lock_guard<std::mutex> lock(mutex_);
        output_stream_ = &out;
    }

   private:
    Level current_level_;
    std::ostream *output_stream_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<std::string> queue_;
    std::thread consume_thread_;
    bool is_exit_;

    SnorlaxLog(Level level = Level::INFO, std::ostream &out = std::cout)
        : current_level_(level), output_stream_(&out), is_exit_(false) {
        consume_thread_ = std::thread(&SnorlaxLog::consume, this);
    }

    ~SnorlaxLog() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            is_exit_ = true;
            cv_.notify_one();
        }

        if (consume_thread_.joinable()) {
            consume_thread_.join();
        }
    }

    std::string getLevelName(Level level) {
        switch (level) {
            case Level::DEBUG:
                return "DEBUG";
            case Level::INFO:
                return "INFO";
            case Level::WARNING:
                return "WARNING";
            case Level::ERROR:
                return "ERROR";
            case Level::CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm *tm = std::localtime(&now_time);
        std::ostringstream oss;
        oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void consume() {
        while (true) {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return !queue_.empty() || is_exit_; });

            while (!queue_.empty()) {
                *output_stream_ << queue_.front() << std::endl;
                queue_.pop();
            }

            if (is_exit_ && queue_.empty()) {
                break;
            }
        }
    }
};
