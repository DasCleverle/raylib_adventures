#include <gfx/color.hpp>
#include <gfx/renderer.hpp>
#include <gfx/window.hpp>

int main() {
    auto& window = gfx::Window::create(1600, 900, "Hello from RAII");

    while (!window.should_close()) {
        auto renderer = window.renderer();

        renderer.clear_background(gfx::Colors::Gray);
        renderer.draw_text(
            "Hello from RAII renderer",
            { 100, 100 },
            50,
            gfx::Colors::Blue
        );
    }
}
