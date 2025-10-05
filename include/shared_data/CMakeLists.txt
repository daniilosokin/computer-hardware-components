set(LIBRARY_NAME
    shared_data
)

add_library(${LIBRARY_NAME}
    STATIC 
        shared_data.cpp
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIBRARY_NAME} 
    Qt6::Core
    Qt6::Widgets
)