#pragma once

#include <functional>
#include <string_view>
#include "gfx/color.hpp"
#include "gfx/font.hpp"
#include "gfx/shader.hpp"
#include "utils/rect.hpp"

namespace gfx {

    class RendererBase {
    public:
        virtual ~RendererBase() = default;

        void clear_background(Color color);

        void draw_text(Font const& font, std::string const& text, Vec2i position, Color color);
        void draw_text(Font const& font, std::u32string_view text, Vec2i position, Color color);

        void draw_rect_filled(RectI rect, Color color);
        void draw_rect_outline(RectI rect, int thickness, Color color);

        void draw_circle_filled(Vec2i center, int radius, Color color);
        void draw_circle_outline(Vec2i center, int radius, Color color);

        void draw_line(Vec2i from, Vec2i to, int thickness, Color color);

        void with_shader(Shader const& shader, std::function<void(RendererBase&)> render);
    };

}  // namespace gfx
