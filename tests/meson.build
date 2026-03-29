r13_shared = declare_dependency(
    link_with: shared,
    include_directories: includes,
    dependencies: [dependency('glfw3'), dependency('glm')]
)

executable(
    'main_tst',
    'main.cc',
    dependencies: r13_shared
)