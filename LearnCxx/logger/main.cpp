
#include "snorlax_log.h"
#include <fstream>
#include <thread>
#include <vector>

int main() {
    std::ofstream file("snorlax_log.txt");

    if (!file.is_open()) {
        std::cerr << "无法打开 log.txt" << std::endl;
        return 1;
    }

    SnorlaxLog::getInstance().setOutputStream(file);
    SnorlaxLog::getInstance().setLevel(Level::DEBUG);

    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([] {
            LOG(Level::DEBUG,
                "线程 ",
                std::this_thread::get_id(),
                " 记录 DEBUG 级别日志。");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            LOG(Level::INFO,
                "线程 ",
                std::this_thread::get_id(),
                " 记录 INFO 级别日志。");
        });
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    return 0;
}
