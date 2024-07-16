#pragma once

#include <string_view>
#include "gfx/color.hpp"
#include "gfx/font.hpp"
#include "utils/rect.hpp"

namespace gfx {

    class RendererBase {
    public:
        virtual ~RendererBase() = default;

        void clear_background(Color color);

        virtual void draw_text(Font const& font, std::string const& text, Vec2i position, Color color);
        virtual void draw_text(Font const& font, std::u32string_view text, Vec2i position, Color color);

        virtual void draw_rect_filled(RectI rect, Color color);
        virtual void draw_rect_outline(RectI rect, int thickness, Color color);

        virtual void draw_circle_filled(Vec2i center, int radius, Color color);
        virtual void draw_circle_outline(Vec2i center, int radius, Color color);

        virtual void draw_line(Vec2i from, Vec2i to, int thickness, Color color);
    };

}  // namespace gfx
