# 启用 CMake 的测试功能
enable_testing()

# 查找并确保 GTest 已安装
find_package(GTest REQUIRED)

# 包含 GTest 的头文件目录
include_directories(${GTEST_INCLUDE_DIRS})

# 添加可执行文件
add_executable(test_config db/test_config.cpp)
add_executable(tests db/test_conn_pool.cpp)

# 查找并包含第三方库的头文件
include_directories(/usr/include/sw/redis++)
include_directories(/usr/include/hiredis)
include_directories(/usr/include/mysql-cppconn-8)
include_directories(/usr/include/boost)

# 链接第三方库的库文件目录
link_directories(/usr/lib64/mysql-cppconn-8)
link_directories(/usr/lib64/boost)

# 为 "test_config" 和 "tests" 可执行文件链接库
target_link_libraries(test_config
    core                # 自定义核心库
    GTest::gtest        # Google Test 库
    GTest::gtest_main   # Google Test 主库
)

target_link_libraries(tests
    core
    GTest::gtest
    GTest::gtest_main
   
)

# 添加测试
add_test(NAME test_config COMMAND test_config)
add_test(NAME test_conn_pool COMMAND tests)
