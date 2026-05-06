cmake_minimum_required(VERSION 3.16)
project(MathTugOfWar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/Player.cpp
    src/ComputerPlayer.cpp
    src/Question.cpp
    src/QuestionGenerator.cpp
    src/TugOfWarBar.cpp
    src/ScoreTracker.cpp
    src/Game.cpp
    main.cpp
)

add_executable(MathTugOfWar ${SOURCES})
