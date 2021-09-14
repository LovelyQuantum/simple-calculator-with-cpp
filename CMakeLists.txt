cmake_minimum_required(VERSION 3.20)
project(calculator)

set(CMAKE_CXX_STANDARD 20)


#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/include)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest)


# 添加下级目录，生成.a文件
add_subdirectory(./googletest)


#set(SOURCE_FLIES main.cpp)
#add_executable(${PROJECT_NAME} ${SOURCE_FLIES} ${SRC_LIST})
add_executable(calculator main.cpp calculator.cpp calculator.h test.cpp)


#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

target_link_libraries(${PROJECT_NAME} gtest)
