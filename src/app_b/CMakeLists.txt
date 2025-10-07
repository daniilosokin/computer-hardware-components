set(SUBPROJECT_NAME
    app_b
)

set(SOURCES
    ${SUBPROJECT_NAME}.cpp
    ${SUBPROJECT_NAME}_window.cpp
)

add_executable(${SUBPROJECT_NAME}
    ${SOURCES}
)

target_include_directories(${SUBPROJECT_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${SUBPROJECT_NAME} 
    PRIVATE
        Qt6::Widgets
        Qt6::Core
        shared_memory
)

set_target_properties(${SUBPROJECT_NAME} 
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)