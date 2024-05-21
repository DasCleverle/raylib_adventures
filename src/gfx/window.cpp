#include <gfx/window.hpp>

#include <raylib.h>
#include <tl/optional.hpp>

#include <gfx/renderer.hpp>

static inline constexpr unsigned int get_flag(gfx::WindowOption option) {
    switch (option) {
        case gfx::WindowOption::Resizeable:
            return FLAG_WINDOW_RESIZABLE;
    }
}

namespace gfx {

    Window::Window(int width, int height, char const* const title) {
        InitWindow(width, height, title);
    }

    Window::~Window() {
        CloseWindow();
    }

    void Window::set_option(WindowOption const option, bool enabled) {
        auto const flag = get_flag(option);

        if (enabled) {
            SetWindowState(flag);
        }
        else {
            ClearWindowState(flag);
        }
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
