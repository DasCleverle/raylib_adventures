#include "gfx/window.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <tl/optional.hpp>

#include "gfx/renderer.hpp"

static inline constexpr unsigned int get_flag(gfx::WindowOption option) {
    switch (option) {
        case gfx::WindowOption::Resizeable:
            return FLAG_WINDOW_RESIZABLE;
        default:
            return 0;
    }
}

namespace gfx {

    Window::Window(int width, int height, char const* const title)
        : m_handle{ std::monostate{} } {
        InitWindow(width, height, title);
    }

    void Window::Deleter::operator()(std::monostate) const {
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

    void Window::set_target_fps(int fps) {
        SetTargetFPS(fps);
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
