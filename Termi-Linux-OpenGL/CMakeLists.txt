cmake_minimum_required(VERSION 3.17)

project(Termi-OpenGL)

file(GLOB SRC CONFIGURE_DEPENDS "imgui/*.cpp")

add_executable(${PROJECT_NAME} ${SRC} glad.c imgui_code.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw)
