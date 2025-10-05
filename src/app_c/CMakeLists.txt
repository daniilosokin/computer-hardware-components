set(SUBPROJECT_NAME
    app_c
)

add_executable(${SUBPROJECT_NAME}
    ${SUBPROJECT_NAME}.cpp
    ${SUBPROJECT_NAME}_window.cpp
)

target_include_directories(${SUBPROJECT_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${SUBPROJECT_NAME} 
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        shared_data
)

set_target_properties(${SUBPROJECT_NAME} 
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)