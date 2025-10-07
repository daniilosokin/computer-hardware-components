set(LIBRARY_NAME
    shared_memory
)

add_library(${LIBRARY_NAME}
    STATIC 
        ${LIBRARY_NAME}.cpp
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIBRARY_NAME} 
    Qt6::Core
    Qt6::Widgets
)