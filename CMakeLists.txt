cmake_minimum_required(VERSION 3.5)
project(MyProject)

# Set the source files explicitly from the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Set the build directory
set(BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Add the executable target
add_executable(main ${SOURCES})

# Set the output directory for the executable
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)
