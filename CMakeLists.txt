cmake_minimum_required(VERSION 3.16)
project(HFCT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_subdirectory(app-a)
add_subdirectory(app-b)
add_subdirectory(app-c)