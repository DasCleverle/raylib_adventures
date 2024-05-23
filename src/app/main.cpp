#include <cstdio>
#include "gfx/color.hpp"
#include "gfx/renderer.hpp"
#include "gfx/window.hpp"

int main() {
    auto& window = gfx::Window::create(1600, 900, "Hello from RAII");

    window.set_option(gfx::WindowOption::Resizeable, false);
    window.set_target_fps(60);

    auto const& font = window.font_manager()
                           .load_font("bitcell", "assets/fonts/bitcell.ttf")
                           .value();

    while (!window.should_close()) {
        auto renderer = window.renderer();

        renderer.clear_background(gfx::Colors::Gray);

        char const* const text = "Hello from RAII renderer";
        int const size = 300;
        Vec2f const text_size = font.measure_text(text, size);

        renderer.draw_rect_filled(
            { 95, 95, text_size.x + 10, text_size.y + 5 },
            gfx::Colors::SkyBlue
        );
        renderer.draw_rect_outline(
            { 95, 95, text_size.x + 10, text_size.y + 5 },
            3,
            gfx::Colors::Black
        );

        renderer.draw_text(font, text, { 100, 100 }, size, gfx::Colors::White);

        renderer.draw_circle_filled({ 300, 300 }, 130, gfx::Colors::White);
    }
}
