glad_lib = static_library(
  'glad',
  sources: ['src/gl.cpp'],
  include_directories: include_directories('include'),
  build_by_default: true,
  install: false
)

glad = declare_dependency(include_directories: include_directories('include'), link_with: glad_lib)
