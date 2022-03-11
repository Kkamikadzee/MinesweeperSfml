cmake_minimum_required(VERSION 3.0.0)
project(Minesweeper VERSION 0.1.0)

include(CTest)
# include(FetchContent)
enable_testing()

# set(SFML_VERSION "2.5.1")

# FetchContent_Declare(
#     sfml
#     GIT_REPOSITORY "https://github.com/SFML/SFML.git"
#     GIT_TAG        "${SFML_VERSION}"
# )

# FetchContent_GetProperties(sfml)
# if(NOT sfml_POPULATED)
#     FetchContent_Populate(sfml)
#     add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
# endif()

set(SFML_STATIC_LIBRARIES TRUE) 

set(SFML_DIR "Dependencies/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system graphics audio REQUIRED)

add_executable(${PROJECT_NAME} src/Game.cpp src/main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-audio)

# target_link_libraries(Minesweeper 
#   PRIVATE
#     sfml-audio
#     sfml-graphics
#     sfml-system
#     sfml-window
# )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
