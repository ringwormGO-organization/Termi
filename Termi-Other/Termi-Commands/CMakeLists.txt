cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Release)

project(Termi-Commands)

set(CMAKE_CXX_FLAGS "-std=c++20 -fpermissive -Wpointer-arith -Wformat-security")

file(GLOB SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries(${PROJECT_NAME})
