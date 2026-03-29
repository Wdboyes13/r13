project('r13', 'cpp', version: '0.1.0')

cpp_compiler_id = meson.get_compiler('cpp').get_id()

includes = []
sources = []
cpp_flags = []
deps = [
    dependency('glfw3'),
    dependency('glm')
]

subdir('scripts')
subdir('lib')
subdir('assets')
subdir('include')
subdir('src')

if cpp_compiler_id == 'msvc'
    cpp_flags += '/DGLFW_INCLUDE_NONE'
else
    cpp_flags += '-DGLFW_INCLUDE_NONE'
endif

shared = shared_library(
    meson.project_name(),
    sources,
    include_directories: includes,
    dependencies: deps,
    install: true,
    cpp_args: cpp_flags
)

static = static_library(
    meson.project_name() + '_static',
    sources,
    include_directories: includes,
    dependencies: deps,
    install: true,
    cpp_args: cpp_flags
)

subdir('tests')
subdir('pkg')