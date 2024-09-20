### C++ 简易日志实现

#### 闲来无事，手搓 C++

欢迎来到 zensnorlax 的博客

在本篇，zen 实现了一个简易 C++ 日志系统。废话不多说，先上代码：

```cpp
#include <chrono>
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
#include <vector>

#define LOG(level, ...)                                                        \
    SnorlaxLog::getInstance().log(level, __FILE__, __LINE__, __VA_ARGS__)

enum class Level { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class SnorlaxLog {
  public:
    static SnorlaxLog &getInstance() {
        static SnorlaxLog logger;
        return logger;
    }

    SnorlaxLog(const SnorlaxLog &) = delete;
    SnorlaxLog &operator=(const SnorlaxLog &) = delete;

    void setLevel(Level level) {
        std::lock_guard<std::mutex> lock(mutex_);
        current_level_ = level;
    }

    template <typename... Args>
    void log(Level level, const char *file, int line, Args... args) {
        if (static_cast<int>(level) >= static_cast<int>(current_level_)) {
            std::ostringstream oss;
            oss << "[" << getCurrentTime() << "] "
                << "[" << std::setw(8) << std::left << getLevelName(level)
                << "] "
                << "[" << file << ":" << line << "] : ";
            (oss << ... << args);

            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(oss.str());
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

    SnorlaxLog(Level level = Level::DEBUG, std::ostream &out = std::cout)
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
```

### 详细设计

#### 1. 构造函数和析构函数

**单例模式**

- `SnorlaxLog` 类使用了单例模式，确保全局只有一个日志实例。这是通过 `getInstance()` 方法实现的：
  ```cpp
  static SnorlaxLog &getInstance() {
      static SnorlaxLog logger;
      return logger;
  }
  ```
  这段代码利用了 C++11 的静态局部变量线程安全特性，确保在多线程环境下也能安全地创建和访问单例。

**私有构造函数**

- 默认构造函数和拷贝构造函数被私有化，防止外部直接创建或复制 `SnorlaxLog` 实例：
  ```cpp
  SnorlaxLog(const SnorlaxLog &) = delete;
  SnorlaxLog &operator=(const SnorlaxLog &) = delete;
  ```

**析构函数**

- 析构函数中，标记 `is_exit_` 为 `true` 并通知消费者线程退出，然后等待消费者线程结束：
  ```cpp
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
  ```

#### 2. 日志级别

**日志级别枚举**

- `Level` 枚举定义了日志级别，支持从 `DEBUG` 到 `CRITICAL` 的各种日志级别：
  ```cpp
  enum class Level { DEBUG, INFO, WARNING, ERROR, CRITICAL };
  ```
  这允许灵活设置日志过滤器。例如，在调试时可以设置为 `DEBUG`，在生产环境中可以设置为 `WARNING` 或 `ERROR`。

#### 3. 不定参数模板

**日志记录**

- `log` 方法使用 C++17 的折叠表达式来处理不定参数，将日志信息格式化为字符串并存入队列：
  ```cpp
  template <typename... Args>
  void log(Level level, const char *file, int line, Args... args) {
      if (static_cast<int>(level) >= static_cast<int>(current_level_)) {
          std::ostringstream oss;
          oss << "[" << getCurrentTime() << "] "
              << "[" << std::setw(8) << std::left << getLevelName(level)
              << "] "
              << "[" << file << ":" << line << "] : ";
          (oss << ... << args);

          {
              std::lock_guard<std::mutex> lock(mutex_);
              queue_.push(oss.str());
              cv_.notify_one();
          }
      }
  }
  ```
  通过 `(oss << ... << args)` 将所有传入的参数逐个插入到 `std::ostringstream` 中，形成最终的日志字符串。

#### 4. 主要逻辑

**消费者线程**

- 构造函数中启动一个消费者线程，该线程在后台处理日志队列：
  ```cpp
  SnorlaxLog(Level level = Level::DEBUG, std::ostream &out = std::cout)
      : current_level_(level), output_stream_(&out), is_exit_(false) {
      consume_thread_ = std::thread(&SnorlaxLog::consume, this);
  }
  ```
  `consume` 方法不断从队列中取出日志并写入 `output_stream_`。

**日志写入**

- 当 `log` 方法被调用时，日志消息会被添加到 `queue_` 中，并通过条件变量 `cv_` 通知消费者线程：
  ```cpp
  std::lock_guard<std::mutex> lock(mutex_);
  queue_.push(oss.str());
  cv_.notify_one();
  ```

**条件变量**

- 消费者线程通过 `cv_.wait()` 等待日志队列有新日志或退出信号：
  ```cpp
  cv_.wait(lock, [this] { return !queue_.empty() || is_exit_; });
  ```

