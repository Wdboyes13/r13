set(GLFW_LIBRARY_TYPE STATIC)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(glm)
list(APPEND LIB_LINKS glm-header-only)

add_subdirectory(glfw)
list(APPEND LIB_LINKS glfw)

add_subdirectory(glad)
list(APPEND LIB_LINKS glad)

add_subdirectory(miniaudio)
list(APPEND LIB_LINKS miniaudio)

add_subdirectory(stbtt)
list(APPEND LIB_LINKS stbtt)

add_subdirectory(stbimg)
list(APPEND LIB_LINKS stbimg)

list(APPEND LIB_LINKS assetlib)

# Export collected third-party targets to the parent CMake scope.
set(LIB_LINKS "${LIB_LINKS}" PARENT_SCOPE)