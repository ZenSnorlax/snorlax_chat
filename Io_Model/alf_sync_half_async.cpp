#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// 定义任务类型
using Task = std::function<void()>;

// 任务队列
class TaskQueue {
  public:
    void push(Task task) {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(std::move(task));
        cv.notify_one();
    }

    Task pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !tasks.empty(); });
        Task task = std::move(tasks.front());
        tasks.pop();
        return task;
    }

  private:
    std::queue<Task> tasks;
    std::mutex mtx;
    std::condition_variable cv;
};

// 线程池
class ThreadPool {
  public:
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (!stop) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(
                            lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty())
                            return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    void enqueue(Task task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.push(std::move(task));
        }
        condition.notify_one();
    }

  private:
    std::vector<std::thread> workers;
    std::queue<Task> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

// 半同步/半异步模式实现
class HalfSyncHalfAsync {
  public:
    HalfSyncHalfAsync(size_t numAsyncThreads) : threadPool(numAsyncThreads) {}

    void addSyncTask(Task task) { taskQueue.push(std::move(task)); }

    void addAsyncTask(Task task) { threadPool.enqueue(std::move(task)); }

    void runSyncTasks() {
        while (true) {
            Task task = taskQueue.pop();
            task();
        }
    }

  private:
    TaskQueue taskQueue;
    ThreadPool threadPool;
};

int main() {
    HalfSyncHalfAsync system(4);

    // 添加异步任务
    system.addAsyncTask([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Async Task 1 executed" << std::endl;
    });

    system.addAsyncTask([] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Async Task 2 executed" << std::endl;
    });

    // 添加同步任务
    system.addSyncTask(
        [] { std::cout << "Sync Task 1 executed" << std::endl; });

    system.addSyncTask(
        [] { std::cout << "Sync Task 2 executed" << std::endl; });

    // 启动同步任务处理
    std::thread syncThread(&HalfSyncHalfAsync::runSyncTasks, &system);

    syncThread.join();
    return 0;
}
