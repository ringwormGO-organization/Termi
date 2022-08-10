cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Debug)

project(Termi-OpenGL)

set(CMAKE_C_FLAGS "-lstdc++ -std=c99")

set(CMAKE_CXX_FLAGS "-std=c++20 -fpermissive -Wpointer-arith -Wformat-security")

# file(GLOB CMBAL CONFIGURE_DEPENDS "Cmbal/src/*.c" "Cmbal/include/*.h") # Uncomment this line if you don't want to use Cmbal in Termi

file(GLOB SRC CONFIGURE_DEPENDS "Commands/*.hpp" "imgui/*.h" "imgui/*.cpp")

add_executable(${PROJECT_NAME} ${CMBAL} ${SRC} glad.c imgui_main.cpp imgui_commands.cpp imgui_code.hpp Translation.hpp main.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw)
