cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Release)

project(Termi-GUI)

set(CMAKE_CXX_FLAGS "-std=c++20")

file(GLOB SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp" "imgui/*.h" "imgui/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SRC} glad.c)

target_link_libraries(${PROJECT_NAME} GL dl glfw json-c)
