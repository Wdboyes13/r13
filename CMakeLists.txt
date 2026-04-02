cmake_minimum_required(VERSION 3.5)

project(
    r13
    LANGUAGES CXX
    VERSION 0.5.0
    DESCRIPTION "A small OpenGL game library"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include(FindPython3)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        "-g"
        "-O0"
        "-fsanitize=address"
    )

    add_link_options("-fsanitize=address")
endif()

set(LIB_LINKS "")
set(bindump ${CMAKE_SOURCE_DIR}/scripts/bindump.py)

add_subdirectory(assets)
add_subdirectory(tests)
add_subdirectory(lib)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "src/*.cc")

add_library(
    ${CMAKE_PROJECT_NAME}
    SHARED
    ${LIB_SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/r13>
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_LINKS})
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE DLL)

include(generate_package)

# Doxygen documentation target
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    
    # Extract INPUT files from Doxyfile using regex
    file(STRINGS ${DOXYFILE} DOXYGEN_INPUT_LINE REGEX "^INPUT\\s*=")
    string(REGEX REPLACE "^INPUT\\s*=\\s*" "" DOXYGEN_INPUT_STRING "${DOXYGEN_INPUT_LINE}")
    string(REPLACE " " ";" DOXYGEN_INPUT_FILES "${DOXYGEN_INPUT_STRING}")
    
    # Convert relative paths to absolute
    set(DOXYGEN_INPUT_FILES_ABS "")
    foreach(file ${DOXYGEN_INPUT_FILES})
        if(NOT IS_ABSOLUTE ${file})
            set(file ${CMAKE_CURRENT_SOURCE_DIR}/${file})
        endif()
        list(APPEND DOXYGEN_INPUT_FILES_ABS ${file})
    endforeach()
    
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${DOXYFILE} ${DOXYGEN_INPUT_FILES_ABS}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
    
    add_custom_target(
        docs ALL
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html
    )
endif()

file(GLOB PRIV_INCLUDES CONFIGURE_DEPENDS "include/r13priv/*")

install(FILES include/r13.h DESTINATION include/r13)
install(DIRECTORY include/r13priv DESTINATION include/r13)