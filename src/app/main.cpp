#include <gfx/color.hpp>
#include <gfx/renderer.hpp>
#include <gfx/window.hpp>

int main() {
    auto& window = gfx::Window::create(1600, 900, "Hello from RAII");
    window.set_option(gfx::WindowOption::Resizeable, false);

    while (!window.should_close()) {
        auto renderer = window.renderer();

        renderer.clear_background(gfx::Colors::Gray);

        char const* const text = "Hello from RAII renderer";
        int const size = 50;
        int const width = renderer.measure_text(text, size);

        renderer.draw_rect_filled(
            { 95, 95, width + 10, size + 5 },
            gfx::Colors::SkyBlue
        );
        renderer.draw_rect_outline(
            { 95, 95, static_cast<float>(width + 10), size + 5 },
            3,
            gfx::Colors::Black
        );
        renderer.draw_text(text, { 100, 100 }, size, gfx::Colors::White);

        renderer.draw_circle_filled({ 300, 300 }, 130, gfx::Colors::White);
    }
}
