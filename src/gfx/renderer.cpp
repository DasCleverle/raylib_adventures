#include "gfx/renderer.hpp"

#include <raylib.h>

using MyColor = gfx::Color;
using RayLibColor = Color;

static inline constexpr RayLibColor to_raylib_color(MyColor color) {
    return {color.r, color.g, color.b, color.a};
}

namespace gfx {
    Renderer::Renderer(Window& window)
        : m_window{window} {

        window.m_renderers++;

        if (window.m_renderers == 1) {
            BeginDrawing();
        }
    }

    Renderer::~Renderer() {
        m_window.m_renderers--;

        if (m_window.m_renderers == 0) {
            EndDrawing();
        }
    }

    void Renderer::clear_background(MyColor color) {
        ClearBackground(to_raylib_color(color));
    }

    void Renderer::draw_fps(Vec2i position) {
        DrawFPS(position.x, position.y);
    }

    void Renderer::draw_text(
        Font const& font,
        std::string const& text,
        Vec2i const position,
        Color const color
    ) {
        DrawTextEx(
            *font.m_handle,
            text.c_str(),
            {static_cast<float>(position.x), static_cast<float>(position.y)},
            font.m_size,
            0,
            to_raylib_color(color)
        );
    }

    void Renderer::draw_rect_filled(RectI const rect, Color const color) {
        DrawRectangle(rect.origin.x, rect.origin.y, rect.size.x, rect.size.y, to_raylib_color(color));
    }

    void Renderer::draw_rect_outline(RectI const rect, int const thickness, Color const color) {
        Rectangle raylib_rect{
            static_cast<float>(rect.origin.x),
            static_cast<float>(rect.origin.y),
            static_cast<float>(rect.size.x),
            static_cast<float>(rect.size.y)
        };

        DrawRectangleLinesEx(raylib_rect, static_cast<float>(thickness), to_raylib_color(color));
    }

    void Renderer::draw_circle_filled(Vec2i const center, int const radius, Color const color) {
        DrawCircle(center.x, center.y, radius, to_raylib_color(color));
    }
}  // namespace gfx
