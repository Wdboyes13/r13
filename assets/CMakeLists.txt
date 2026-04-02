file(GLOB _assets RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" CONFIGURE_DEPENDS 
    "*.frag"
    "*.vert"
    "*.ttf"
)

set(asset_files "")
foreach(asset IN LISTS _assets)
    string(REGEX REPLACE "[^a-zA-Z0-9]" "_" fname "${asset}")
    set(output "${CMAKE_CURRENT_BINARY_DIR}/${fname}.cc")
    add_custom_command(
        OUTPUT ${output}
        COMMAND ${Python3_EXECUTABLE} ${bindump} ${CMAKE_CURRENT_SOURCE_DIR}/${asset} ${fname} ${output}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${asset} ${bindump}
    )
    list(APPEND asset_files ${output})
endforeach()

add_library(assetlib STATIC ${asset_files})