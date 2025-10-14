cmake_minimum_required(VERSION 3.10)
project(Chess_Man-Machine_Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt5 setup
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(chesscore
    define.h
    CMoveGenerator.h
    CMoveGenerator.cpp
    CSearchEngine.h
    CSearchEngine.cpp
    CEveluation.h
    CEveluation.cpp
    CNegaMaxEngine.h
    CNegaMaxEngine.cpp
)

target_include_directories(chesscore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(chess_app
    src/main.cpp
    src/BoardWidget.h
    src/BoardWidget.cpp
    src/MainWindow.h
    src/MainWindow.cpp
    src/GameState.h
    src/GameState.cpp
)

target_include_directories(chess_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(chess_app PRIVATE chesscore Qt5::Widgets)
