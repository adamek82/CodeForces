cmake_minimum_required(VERSION 3.15)
project(CodeForces)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Add include directories
include_directories(${INCLUDE_DIR})  # Ensures include/ headers are found

# Collect all source files
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

# Create executable
add_executable(CodeForces ${SOURCES})

# Set MSVC specific compiler flags
if (MSVC)
    target_compile_options(CodeForces PRIVATE /W4 /WX)
endif()

# Set output directory
set_target_properties(CodeForces PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
