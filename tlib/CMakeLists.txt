cmake_minimum_required(VERSION 3.16)

project(tlib-test)

set(CMAKE_CXX_FLAGS "-Wcpp")

file(GLOB SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
