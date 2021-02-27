cmake_minimum_required(VERSION 3.13.4)

project(sudoku-sfml)

add_subdirectory(sources)

add_executable(${PROJECT_NAME} sources/main.cpp)

# Downloads Submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "S{PROJECT_SOURCE_DIR}/.git")

# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE}
                        submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Check each submodules
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/sfml/CMakeLists.txt")
    message(FATAL_ERROR "The sfml submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodule sfml")
endif()

add_subdirectory(external/sfml)

add_library(
   Animation sources/Animation.cpp sources/Animation.h
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/sfml/include
    PUBLIC sources/
)

target_link_directories(${PROJECT_NAME} 
    PUBLIC external/sfml/src
    PUBLIC sources/
)

target_link_libraries(${PROJECT_NAME}
    sfml-audio
    sfml-graphics
    sfml-network
    sfml-system
    sfml-window
    animation
)


