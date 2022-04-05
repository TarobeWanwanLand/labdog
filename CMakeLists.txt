# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.9)

# Set project name and version
project(labdog VERSION 1.0.0)

# Set environment variables
include(${PROJECT_SOURCE_DIR}/cmake/SetupEnvironment.cmake)

# Library sources
add_subdirectory(cmake/labdog)
add_subdirectory(example)
