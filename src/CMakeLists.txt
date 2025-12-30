file(GLOB_RECURSE EGEN_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE EGEN_HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# Register any C sources (e.g., GLAD implementation) so they're built into the library
file(GLOB_RECURSE EGEN_CSOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(egen STATIC ${EGEN_SOURCES} ${EGEN_HEADERS} ${EGEN_CSOURCES})

target_include_directories(egen
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/glad/include
)

find_package(OpenGL REQUIRED)

target_link_libraries(egen
        PUBLIC glfw OpenGL::GL
)
