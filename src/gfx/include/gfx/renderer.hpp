#pragma once

#include "color.hpp"
#include "utils/rect.hpp"
#include "utils/vec2.hpp"
#include "window.hpp"

namespace gfx {
    class Renderer final {
        friend class Window;

    private:
        Window& m_window;

        Renderer(Window& window);

    public:
        Renderer(Renderer const&) = delete;
        Renderer(Renderer&&) = delete;
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
        [[nodiscard]] int measure_text(char const* const text, int const size);

        void draw_rect_filled(RectI const rect, Color const color);
        void draw_rect_outline(
            RectF const rect,
            float const thickness,
            Color const color
        );

        void draw_circle_filled(
            Vec2i const center,
            int const radius,
            Color const color
        );
        void draw_circle_outline(
            Vec2i const center,
            int const radius,
            float const thickness,
            Color const color
        );
    };
}  // namespace gfx
