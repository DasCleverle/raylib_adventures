#include <gfx/window.hpp>

#include <raylib.h>
#include <tl/optional.hpp>

#include <gfx/renderer.hpp>

namespace gfx {

    Window::Window(int width, int height, char const* const title) {
        InitWindow(width, height, title);
    }

    Window::~Window() {
        CloseWindow();
    }

    [[nodiscard]] bool Window::should_close() const {
        return WindowShouldClose();
    }

    [[nodiscard]] Vec2i Window::size() const {
        return { GetScreenWidth(), GetScreenHeight() };
    }

    [[nodiscard]] Renderer Window::renderer() {
        return Renderer{ *this };
    }
}  // namespace gfx
