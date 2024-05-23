add_library(gfx STATIC
    include/gfx/window.hpp
    window.cpp
    include/gfx/renderer.hpp
    renderer.cpp
    include/gfx/color.hpp
    include/gfx/font.hpp
    font.cpp
    include/gfx/font_manager.hpp
    include/gfx/font_config.hpp
)

target_include_directories(gfx PUBLIC include)

target_link_libraries(gfx PRIVATE
    raylib

    PUBLIC
    utils

    tl::optional)
