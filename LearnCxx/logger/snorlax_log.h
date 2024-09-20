#ifndef SNORLAX_LOG_H
#define SNORLAX_LOG_H

#include <condition_variable>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>

enum class Level { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class SnorlaxLog {
  public:
    static SnorlaxLog &getInstance();
    SnorlaxLog(const SnorlaxLog &) = delete;
    SnorlaxLog &operator=(const SnorlaxLog &) = delete;

    void setLevel(Level level);

    template <typename... Args>
    void log(Level level, const char *file, int line, Args... args) {
        if (static_cast<int>(level) >= static_cast<int>(current_level_)) {
            std::ostringstream oss;
            oss << "[" << getCurrentTime() << "] "
                << "[" << getLevelName(level)
                << "] "
                << "[" << file << ":" << line << "] : ";
            (oss << ... << args);

            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(std::move(oss.str()));
                cv_.notify_one();
            }
        }
    }

    void setOutputStream(std::ostream &out);

  private:
    SnorlaxLog(Level level = Level::DEBUG, std::ostream &out = std::cout);
    ~SnorlaxLog();

    std::string getLevelName(Level level);
    std::string getCurrentTime();
    void consume();

    Level current_level_;
    std::ostream *output_stream_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<std::string> queue_;
    std::thread consume_thread_;
    bool is_exit_;
};

#define LOG(level, ...)                                                        \
    SnorlaxLog::getInstance().log(level, __FILE__, __LINE__, __VA_ARGS__)

#endif // SNORLAX_LOG_H

