cmake_minimum_required(VERSION 3.10)
project(musicbib)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(musicbib src/main.cpp src/MusicTitle.cpp src/LibraryProvider.cpp)
