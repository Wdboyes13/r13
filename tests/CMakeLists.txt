file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sprite.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
add_executable(
    test_main
    main.cc
)

target_link_libraries(test_main PRIVATE ${CMAKE_PROJECT_NAME})