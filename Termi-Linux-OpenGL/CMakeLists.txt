cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Debug)

project(Termi-OpenGL)

file(GLOB SRC CONFIGURE_DEPENDS "imgui/*.hpp" "imgui/*.cpp")

add_executable(${PROJECT_NAME} ${SRC} glad.c imgui_code.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw)
