cmake_minimum_required(VERSION 3.17)

project(Termi-OpenGL)

add_executable(${PROJECT_NAME} imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_impl_glfw.cpp imgui/imgui_impl_opengl3.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp glad.c imgui_code.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} GL dl glfw)
