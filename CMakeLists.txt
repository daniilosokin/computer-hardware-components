cmake_minimum_required(VERSION 3.30)
project(computer-hardware-components)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 
    REQUIRED COMPONENTS 
        Core 
        Widgets
)

add_subdirectory(./include)
add_subdirectory(src)