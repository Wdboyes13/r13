project('r13_renderer', 'cpp', version: '0.1.0')

fs = import('fs')
xxd = find_program('xxd')

subdir('lib/glad')
subdir('assets')

asset_hdrs = []
foreach asset : assets
    fname = fs.name(asset).underscorify()
    header = custom_target(
        fname + '_cdata',
        input: asset,
        output: fname + '.cc',
        command: [xxd, '-i', '-n', fname, '@INPUT@'],
        capture: true
    )
    asset_hdrs += header
endforeach

sources = [
    asset_hdrs,
    'src/circ_rnd.cc',
    'src/r13r.cc',
    'src/shader.cc',
    'src/square_rnd.cc',
    'src/text_rnd.cc'
]

includes = include_directories('include')

deps = [
    glad,
    dependency('glfw3'),
    dependency('glm'),
    dependency('freetype2')
]

shared = shared_library(
    meson.project_name(),
    sources,
    include_directories: includes,
    dependencies: deps,
    install: true
)

static = static_library(
    meson.project_name() + '_static',
    sources,
    include_directories: includes,
    dependencies: deps,
    install: true
)

pkg = import('pkgconfig')

pkg.generate(
    shared,
    name: shared.name(),
    description: 'R13 OpenGL Game Library (shared library)',
    version: meson.project_version(),
    install: true
)

pkg.generate(
    static,
    name: static.name(),
    description: 'R13 OpenGL Game Library (static library)',
    version: meson.project_version(),
    install: true
)