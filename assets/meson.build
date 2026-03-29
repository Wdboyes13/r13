fs = import('fs')
py = find_program('python3', 'python')

_assets = files(
  'circle.frag',
  'circle.vert',
  'rect.frag',
  'rect.vert',
  'text.frag',
  'text.vert',
  'vt323.ttf'
)

asset_files = []
foreach asset : _assets
    fname = fs.name(asset).underscorify()
    asset_files += custom_target(
        fname + '_cdata',
        input: asset,
        output: fname + '.cc',
        command: [py, bindump, '@INPUT@', fname],
        capture: true
    )
endforeach

asset_lib = static_library(
    'assetlib',
    asset_files
)

assets = declare_dependency(
    link_with: asset_lib
)