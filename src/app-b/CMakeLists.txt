cmake_minimum_required(VERSION 3.30)
project(app-b LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    app_b.cpp
    app_b_window.cpp
    app_b_window.hpp
    app_b_window_ui.h
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)