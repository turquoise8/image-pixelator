
cmake_minimum_required(VERSION 3.10)
project(ImagePixelator C)

 # Set the C standard
set(CMAKE_C_STANDARD 99)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the 'include' directory to the header search paths
include_directories(include)

# Add all source files under the src directory
file(GLOB SRC_FILES "src/*.c")

# Create an executable from the source files
add_executable(pixelator ${SRC_FILES})

target_link_libraries(pixelator m)
