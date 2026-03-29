cmake_minimum_required(VERSION 3.5)

project(
    r13
    LANGUAGES CXX
    VERSION 0.3.0
    DESCRIPTION "A small OpenGL game library"
)

include(FindPython3)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(bindump ${CMAKE_SOURCE_DIR}/scripts/bindump.py)

add_subdirectory(assets)
add_subdirectory(tests)
add_subdirectory(lib)

file(GLOB LIB_SOURCES "src/*.cc")

add_library(
    ${CMAKE_PROJECT_NAME}
    SHARED
    ${LIB_SOURCES}
)

add_library(
    ${CMAKE_PROJECT_NAME}_static
    STATIC
    ${LIB_SOURCES}
)

set(EXPORT_LIBS ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_static)

foreach(lib IN LISTS EXPORT_LIBS)
    target_include_directories(${lib} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/r13>
    )
    target_link_libraries(${lib} PUBLIC glfw miniaudio glm-header-only)
    target_link_libraries(${lib} PRIVATE assetlib stbtt glad)
    target_compile_definitions(${lib} PRIVATE GLFW_INCLUDE_NONE)
endforeach()

include(generate_package)

install(DIRECTORY include/ DESTINATION include/r13)
