cmake_minimum_required(VERSION 3.5.0)
project(snorlax_chat VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

# python
set(PYTHON_SCRIPT "${CMAKE_SOURCE_DIR}/script/init.py")

execute_process(
    COMMAND python3 ${PYTHON_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/script
    RESULT_VARIABLE result
)

if(result EQUAL 0)
    message(STATUS "Python script executed successfully.")
else()
    message(FATAL_ERROR "Python script failed with error code ${result}.")
endif()

# mysql
add_definitions(-DSTATIC_CONCPP)

include_directories(/usr/include/mysql-cppconn-8)

include_directories(include)  

add_executable(snorlax_chat ${SOURCE_FILES})

set(SNORLAX_MYSQL "/usr/lib64/libmysqlcppconnx-static.a" "ssl" "crypto" "resolv" )
target_link_libraries(snorlax_chat
    ${SNORLAX_MYSQL}
)


# test
enable_testing()  
find_package(GTest REQUIRED)  
include_directories(${GTEST_INCLUDE_DIRS})  

set(TEST_FILES test/test_main.cpp test/test_connPool.cpp) 

add_executable(snorlax_chat_tests ${TEST_FILES}) 

target_link_libraries(snorlax_chat_tests
    ${GTEST_LIBRARIES}  
    pthread 
    ${SNORLAX_MYSQL}    
)

add_test(NAME snorlax_chat_tests COMMAND snorlax_chat_tests)
