cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Debug)

project(Termi-Commands)

IF(WIN32)
    set(CMAKE_CXX_FLAGS "/EHsc /std:c++20")
ELSE()
    set(CMAKE_CXX_FLAGS "-std=c++20")
ENDIF()

file(GLOB SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries(${PROJECT_NAME})
