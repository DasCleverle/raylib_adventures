add_library(gfx STATIC

    font.cpp
    include/gfx/color.hpp
    include/gfx/font.hpp
    include/gfx/font_config.hpp
    include/gfx/font_manager.hpp
    include/gfx/render_buffer.hpp
    include/gfx/renderer.hpp
    include/gfx/renderer_base.hpp
    include/gfx/shader.hpp
    include/gfx/window.hpp
    render_buffer.cpp
    renderer.cpp
    renderer_base.cpp
    shader.cpp
    window.cpp

)

target_include_directories(gfx PUBLIC include)

target_link_libraries(gfx PRIVATE
    raylib

    PUBLIC
    utils

    tl::optional)
