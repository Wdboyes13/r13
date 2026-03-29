stbtt_lib = static_library(
  'stb_truetype',
  sources: ['src/stb_truetype.cc'],
  include_directories: include_directories('include'),
  build_by_default: true,
  install: false
)

stbtt = declare_dependency(
    include_directories: include_directories('include'), 
    link_with: stbtt_lib
)
