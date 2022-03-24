cmake_minimum_required(VERSION 3.16)

project(pkg)

file(GLOB SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

if(MSVC)
    set(requiredlibs)
    find_package(CURL)
    if(CURL_FOUND)
        set(requiredlibs ${requiredlibs} ${CURL_LIBRARIES})
        add_definitions(-DCURL_STATICLIB)
    else(CURL_FOUND)
        message(FATAL_ERROR "Could not find the CURL library and development files.")
    endif()
else()
    set(CMAKE_BUILD_TYPE Debug CURL_LIBRARY "-lcurl")
    find_package(CURL REQUIRED)
endif()

add_executable(${PROJECT_NAME} ${SRC})

include_directories(${CURL_INCLUDE_DIR})

if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
else()
    target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()
