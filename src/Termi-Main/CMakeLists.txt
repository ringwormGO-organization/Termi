cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Release)

project(Termi-Main)

IF(WIN32)
    set(CMAKE_CXX_FLAGS "/EHsc /std:c++20")
ELSE()
    set(CMAKE_CXX_FLAGS "-std=c++20 -g")
ENDIF()

file(GLOB SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME})
