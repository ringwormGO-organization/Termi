cmake_minimum_required(VERSION 3.16)

project(tlib)

set(CMAKE_CXX_FLAGS)

file(GLOB SRC CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
