cmake_minimum_required(VERSION 3.29)
project(egen)

set(CMAKE_CXX_STANDARD 23)

# Options
option(BUILD_EXAMPLES "Build the examples" ON)

# External dependencies
add_subdirectory(external/glfw)

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
