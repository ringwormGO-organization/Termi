cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Release)

project(Termi-GUI)

IF(WIN32)
    set(CMAKE_CXX_FLAGS "/EHsc /std:c++20")
ELSE()
    set(CMAKE_CXX_FLAGS "-std=c++20")
ENDIF()

file(GLOB SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp" "imgui/*.h" "imgui/*.cpp")

IF(WIN32)
    set(json-c_DIR "C:\\src\\vcpkg\\installed\\x64-windows-static\\share\\json-c")
    set(ZeroMQ_DIR "C:\\src\\vcpkg\\installed\\x64-windows\\share\\zeromq")
    set(cppzmq_DIR "C:\\src\\vcpkg\\installed\\x64-windows\\share\\cppzmq")

    find_package(json-c CONFIG REQUIRED)
    find_package(ZeroMQ CONFIG REQUIRED)
    find_package(cppzmq CONFIG REQUIRED)
    
    add_library(${PROJECT_NAME} SHARED ${SRC} glad.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE json-c::json-c libzmq cppzmq opengl32 glfw3)
ELSE()
    add_library(${PROJECT_NAME} SHARED ${SRC} glad.c)
    target_link_libraries(${PROJECT_NAME} GL dl glfw json-c zmq)
ENDIF()
