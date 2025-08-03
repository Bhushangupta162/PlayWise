cmake_minimum_required(VERSION 3.10)
project(PlayWise)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(playwise ${SOURCES})
add_executable(test_playwise
    tests/test_main.cpp
    src/PlaylistEngine.cpp
    src/utils.cpp
    src/Sorter.cpp
    src/RatingTree.cpp
    src/SongIndex.cpp
    src/PlaybackHistory.cpp
    src/ArtistBlocker.cpp
    src/DurationAnalyzer.cpp
)

target_include_directories(test_playwise PRIVATE include)

