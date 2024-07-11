#pragma once

#include "gfx/color.hpp"
#include "gfx/font.hpp"
#include "utils/rect.hpp"

namespace gfx {

    class RendererBase {
    public:
        virtual ~RendererBase() = default;

        void clear_background(Color const color);

        virtual void draw_text(
            Font const& font_type,
            std::string const& text,
            Vec2i const position,
            Color const color
        );

        virtual void draw_rect_filled(RectI const rect, Color const color);
        virtual void draw_rect_outline(RectI const rect, int const thickness, Color const color);

        virtual void draw_circle_filled(Vec2i const center, int const radius, Color const color);
        virtual void draw_circle_outline(Vec2i const center, int const radius, Color const color);

        virtual void draw_line(Vec2i from, Vec2i to, int const thickness, Color const color);
    };

}  // namespace gfx
