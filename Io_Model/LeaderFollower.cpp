#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using Task = std::function<void()>;

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

class LeaderFollower {
  public:
    LeaderFollower(size_t numThreads) : stop(false), leaderThreadId(-1) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back(&LeaderFollower::workerThread, this, i);
        }
    }

    ~LeaderFollower() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
            cv.notify_all();
        }
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    void addTask(Task task) { taskQueue.push(std::move(task)); }

  private:
    void workerThread(int threadId) {
        while (true) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                while (!stop && leaderThreadId != threadId) {
                    cv.wait(lock);
                }
                if (stop)
                    return;

                leaderThreadId = threadId;
                task = taskQueue.pop();
            }

            try {
                task();
            } catch (const std::exception &e) {
                // 处理任务中的异常，避免线程退出
                std::cerr << "Task exception: " << e.what() << std::endl;
            }

            {
                std::unique_lock<std::mutex> lock(mtx);
                leaderThreadId = -1;
                cv.notify_one(); // 只通知一个等待线程，减少不必要的唤醒
            }
        }
    }

    TaskQueue taskQueue;
    std::vector<std::thread> workers;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;
    int leaderThreadId;
};

int main() {
    LeaderFollower system(4);

    // 添加任务
    system.addTask([] {
        std::cout << "Task 1 executed by thread " << std::this_thread::get_id()
                  << std::endl;
    });

    system.addTask([] {
        std::cout << "Task 2 executed by thread " << std::this_thread::get_id()
                  << std::endl;
    });

    system.addTask([] {
        std::cout << "Task 3 executed by thread " << std::this_thread::get_id()
                  << std::endl;
    });

    // 模拟一些延迟以观察任务执行
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
