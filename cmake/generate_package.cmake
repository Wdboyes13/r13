configure_file(${CMAKE_SOURCE_DIR}/cmake/r13.pc.in r13.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/r13.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

include(CMakePackageConfigHelpers)

install(
    TARGETS r13 r13_static miniaudio glm-header-only glfw assetlib stbtt glad
    EXPORT r13Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/r13
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/r13
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/r13
)

install(EXPORT r13Targets
    FILE r13Targets.cmake
    NAMESPACE r13::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r13
)

write_basic_package_version_file(
    r13ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
)

configure_package_config_file(
    cmake/r13Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/r13Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r13
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/r13Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/r13ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r13
)