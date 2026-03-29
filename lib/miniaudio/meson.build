ma_lib = static_library(
  'miniaudio',
  sources: ['src/miniaudio.cc'],
  include_directories: include_directories('include'),
  build_by_default: true,
  install: false
)

ma = declare_dependency(
    include_directories: include_directories('include'), 
    link_with: ma_lib
)

install_headers(
    'include/miniaudio.h',
    subdir: 'r13'
)

deps += ma