cmake_minimum_required(VERSION 3.10)
project(MusicLibrary)

set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(include)

# Add GoogleTest
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

# Add library
add_library(musiclib
    src/MusicTitle.cpp
    src/LibraryProvider.cpp
)

# Add executable
add_executable(musicbib
    src/main.cpp
)

# Link library to executable
target_link_libraries(musicbib musiclib)

# Add test executable
add_executable(runTests
    tests/test_main.cpp
    tests/test_LibraryProvider.cpp
)

# Link GoogleTest and library to test executable
target_link_libraries(runTests gtest gtest_main musiclib)

# Enable testing
enable_testing()
add_test(NAME runTests COMMAND runTests)
