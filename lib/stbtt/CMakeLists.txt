add_library(
    stbtt STATIC
    src/stb_truetype.cc
)

target_include_directories(stbtt PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/r13>
)

install(DIRECTORY include/ DESTINATION include/r13)