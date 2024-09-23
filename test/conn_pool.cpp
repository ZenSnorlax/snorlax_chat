#include "../conn_pool/conn_pool.hpp"

#include <chrono>
#include <thread>
#include <vector>

int main() {
    const std::string host = "localhost";
    const std::string user = "abs";
    const std::string password = "1510017673";
    const std::string dbName = "snorlax_chat";

    auto& log = SnorlaxLog::getInstance();

    log.setLevel(Level::DEBUG);

    SQLConfig sql_config{host, user, 33060, password, dbName};
    SQLConnPool& pool = SQLConnPool::getInstance(std::move(sql_config));

    std::vector<std::thread> threads;

    for (int i = 0; i < 50; i++) {
        threads.emplace_back([&pool] {
            auto conn = pool.getConnection();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            pool.releaseConnection(std::move(conn));
        });
    }

    for (auto& t : threads) t.join();
}