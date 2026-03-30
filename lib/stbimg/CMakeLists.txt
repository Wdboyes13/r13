add_library(
    stbimg STATIC
    src/stb_image.cc
)

target_include_directories(stbimg PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/r13>
)