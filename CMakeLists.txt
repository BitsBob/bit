cmake_minimum_required(VERSION 3.10)
project(SimpleScannerProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Scan src directory for all .cpp files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Set executable output directory
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include src folder for headers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
