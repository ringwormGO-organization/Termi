cmake_minimum_required(VERSION 3.16)

project(Termi)

file(GLOB SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
