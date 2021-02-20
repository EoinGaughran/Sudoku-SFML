cmake_minimum_required(VERSION 3.13.4)

project(sudoku-sfml)

add_subdirectory(sources)

add_executable(${PROJECT_NAME} sources/main.cpp)

add_subdirectory(external/sfml)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/sfml/include
)

target_link_directories(${PROJECT_NAME} 
    PUBLIC external/sfml/src
)

target_link_libraries(${PROJECT_NAME}
    sfml-audio
    sfml-graphics
    sfml-network
    sfml-system
    sfml-window
)


