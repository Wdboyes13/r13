add_library(
    glad STATIC
    src/gl.cc
)

target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/r13>
)

install(DIRECTORY include/ DESTINATION include/r13)