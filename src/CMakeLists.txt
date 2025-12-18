file(GLOB_RECURSE EGEN_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE EGEN_HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_library(egen STATIC ${EGEN_SOURCES} ${EGEN_HEADERS})

target_include_directories(egen
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(egen
        PUBLIC glfw
)