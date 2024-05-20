#pragma once

#include <utils/vec2.hpp>

#include "color.hpp"
#include "window.hpp"

namespace gfx {
    class Renderer final {
        friend class Window;

    private:
        Window& m_window;

        Renderer(Window& window);

    public:
        Renderer(Renderer const&) = delete;
        Renderer(Renderer&&) = default;
        Renderer& operator=(Renderer const&) = delete;
        Renderer& operator=(Renderer&&) = delete;
        ~Renderer();

        void clear_background(Color const color);
        void draw_text(
            char const* const text,
            Vec2i const position,
            int const size,
            Color const color
        );
    };
}  // namespace gfx
