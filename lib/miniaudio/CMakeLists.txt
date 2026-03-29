add_library(
    miniaudio STATIC
    src/miniaudio.cc
)

target_include_directories(miniaudio PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/r13>
)