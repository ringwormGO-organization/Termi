cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Debug)

project(Termi-Main)

set(CMAKE_CXX_FLAGS "-std=c++20 -fpermissive")

file(GLOB SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} GL dl glfw)
