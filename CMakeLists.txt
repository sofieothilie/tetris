# Specify the minimum CMake version required by this project.
# CMake will refuse to configure the project if an older version is used.
cmake_minimum_required(VERSION 3.22)

# Define the project name and the programming languages used.
#
# C++ is used for the host-side unit tests based on Google Test.
# Assembly (ASM) is used for low-level startup code, such as the
# reset handler and interrupt vector table that execute before main().
project(Tetris LANGUAGES CXX)

# Configure the C language standard used by the project.
# C11 is widely supported and provides a good baseline for embedded development.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(tetris
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/include/MainWindow.hpp

    src/ui/GameWidget.cpp
    src/ui/include/GameWidget.hpp
    src/ui/BoardRenderer.cpp
    src/ui/include/BoardRenderer.hpp

    src/game/Board.cpp
    src/game/Game.cpp
    src/game/Pieces.cpp
)

target_include_directories(tetris PRIVATE
    ${CMAKE_SOURCE_DIR}/src/ui/include
    ${CMAKE_SOURCE_DIR}/src/game/include
    ${CMAKE_SOURCE_DIR}/src/game
)

target_link_libraries(tetris PRIVATE
    Qt6::Widgets
)