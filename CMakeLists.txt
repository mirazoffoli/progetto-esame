cmake_minimum_required(VERSION 3.0)
project(MyProject)

# Set the source files
file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

# Set the build directory
set(BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Create the build directory if it doesn't exist
file(MAKE_DIRECTORY ${BUILD_DIR})

# Add the executable target
add_executable(MyExecutable ${SOURCES})

# Set the output directory for the executable
set_target_properties(MyExecutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)