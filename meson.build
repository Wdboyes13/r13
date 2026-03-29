project('r13_renderer', 'cpp', version: '0.1.0')

bindump = files('scripts/bindump.py')

subdir('lib')
subdir('assets')

sources = [
    'src/circ_rnd.cc',
    'src/r13r.cc',
    'src/shader.cc',
    'src/square_rnd.cc',
    'src/text_rnd.cc'
]

includes = include_directories('include')

deps = [
    glad, assets, stbtt,
    dependency('glfw3'),
    dependency('glm'),
    dependency('freetype2')
]

shared = shared_library(
    meson.project_name(),
    sources,
    include_directories: includes,
    dependencies: deps,
    install: true,
    cpp_args: ['-DGLFW_INCLUDE_NONE']
)

static = static_library(
    meson.project_name() + '_static',
    sources,
    include_directories: includes,
    dependencies: deps,
    install: true,
    cpp_args: ['-DGLFW_INCLUDE_NONE']
)

pkg = import('pkgconfig')

pkg.generate(
    shared,
    name: shared.name(),
    description: 'R13 OpenGL Game Library (shared library)',
    version: meson.project_version()
)

pkg.generate(
    static,
    name: static.name(),
    description: 'R13 OpenGL Game Library (static library)',
    version: meson.project_version()
)

# this will just be used by tests
r13_shared = declare_dependency(
    link_with: shared,
    include_directories: includes,
    dependencies: [dependency('glfw3'), dependency('glm')]
)

subdir('tests')