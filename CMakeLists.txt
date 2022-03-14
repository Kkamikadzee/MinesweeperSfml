cmake_minimum_required(VERSION 3.0.0)
project(Minesweeper VERSION 0.1.0)

include(CTest)
enable_testing()

set(SFML_STATIC_LIBRARIES TRUE) 

set(SFML_DIR "Dependencies/SFML-2.5.1/lib/cmake/SFML")

set(Boost_DEBUG ON)
set(Boost_USE_STATIC_LIBS TRUE)
set(Boost_ARCHITECTURE -x64)

set(BOOST_ROOT "Dependencies/boost_1_78_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/boost")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")

find_package(SFML 2.5.1 REQUIRED COMPONENTS system graphics audio)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(${PROJECT_NAME} 
    src/GameData.cpp
    src/GameLogic.cpp
    src/GameView.cpp
    src/Game.cpp 
    src/main.cpp
)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-audio)

target_link_libraries(${PROJECT_NAME} Boost::program_options)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
