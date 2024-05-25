#pragma once

#include "utils/rect.hpp"
#include "utils/vec2.hpp"

#include "color.hpp"
#include "font.hpp"
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
        void draw_fps(Vec2f position);

        void draw_text(char const* const text, Vec2f const position, int const size, Color const color);
        void draw_text(
            Font const& font_type,
            char const* const text,
            Vec2f const position,
            Color const color
        );

        void draw_rect_filled(RectF const rect, Color const color);
        void draw_rect_outline(RectF const rect, float const thickness, Color const color);

        void draw_circle_filled(Vec2f const center, int const radius, Color const color);
        void draw_circle_outline(
            Vec2f const center,
            int const radius,
            float const thickness,
            Color const color
        );
    };
}  // namespace gfx
