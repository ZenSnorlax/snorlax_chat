#include "snorlax_log.h"
#include <chrono>
#include <ctime>

SnorlaxLog &SnorlaxLog::getInstance() {
    static SnorlaxLog logger;
    return logger;
}

SnorlaxLog::SnorlaxLog(Level level, std::ostream &out)
    : current_level_(level), output_stream_(&out), is_exit_(false) {
    consume_thread_ = std::thread(&SnorlaxLog::consume, this);
}

SnorlaxLog::~SnorlaxLog() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        is_exit_ = true;
        cv_.notify_one();
    }

    if (consume_thread_.joinable()) {
        consume_thread_.join();
    }
}

void SnorlaxLog::setLevel(Level level) {
    std::lock_guard<std::mutex> lock(mutex_);
    current_level_ = level;
}

void SnorlaxLog::setOutputStream(std::ostream &out) {
    std::lock_guard<std::mutex> lock(mutex_);
    output_stream_ = &out;
}

std::string SnorlaxLog::getLevelName(Level level) {
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

std::string SnorlaxLog::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *tm = std::localtime(&now_time);
    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void SnorlaxLog::consume() {
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
