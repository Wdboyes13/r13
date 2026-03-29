cmake_minimum_required(VERSION 3.5)

project(
    r13
    LANGUAGES CXX
    VERSION 0.5.0
    DESCRIPTION "A small OpenGL game library"
)

include(FindPython3)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(bindump ${CMAKE_SOURCE_DIR}/scripts/bindump.py)

add_subdirectory(assets)
add_subdirectory(tests)
add_subdirectory(lib)

file(GLOB LIB_SOURCES CONFIGURE_DEPENDS "src/*.cc")

add_library(
    ${CMAKE_PROJECT_NAME}
    SHARED
    ${LIB_SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/r13>
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE assetlib stbtt glad glfw miniaudio glm-header-only)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE DLL)

include(generate_package)

file(GLOB PRIV_INCLUDES CONFIGURE_DEPENDS "include/r13priv/*")

install(FILES include/r13.h DESTINATION include/r13)
install(DIRECTORY include/r13priv DESTINATION include/r13)