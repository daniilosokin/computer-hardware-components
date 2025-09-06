cmake_minimum_required(VERSION 3.16)
project(app-c LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    main_window.cpp
    main_window.hpp
)

set(FORMS
    main_window.ui
)

qt6_wrap_cpp(MOC_FILES ${HEADERS})
qt6_wrap_ui(UI_FILES ${FORMS})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${FORMS}
    ${MOC_FILES}
    ${UI_FILES}
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