#include "gfx/renderer.hpp"

#include <raylib.h>

using MyColor = gfx::Color;
using RayLibColor = Color;

static inline constexpr RayLibColor to_raylib_color(MyColor color) {
    return { color.r, color.g, color.b, color.a };
}

namespace gfx {
    Renderer::Renderer(Window& window) : m_window{ window } {
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

    void Renderer::draw_text(
        char const* const text,
        Vec2f position,
        int size,
        Color color
    ) {
        DrawText(text, position.x, position.y, size, to_raylib_color(color));
    }

    void Renderer::draw_text(
        Font const& font,
        char const* const text,
        Vec2f const position,
        int const size,
        Color const color
    ) {
        DrawTextEx(
            *font.m_handle,
            text,
            { static_cast<float>(position.x), static_cast<float>(position.y) },
            size,
            0,
            to_raylib_color(color)
        );
    }

    void Renderer::draw_rect_filled(RectF const rect, Color const color) {
        DrawRectangle(
            rect.origin.x,
            rect.origin.y,
            rect.size.x,
            rect.size.y,
            to_raylib_color(color)
        );
    }

    void Renderer::draw_rect_outline(
        RectF const rect,
        float const thickness,
        Color const color
    ) {
        DrawRectangleLinesEx(
            { rect.origin.x, rect.origin.y, rect.size.x, rect.size.y },
            thickness,
            to_raylib_color(color)
        );
    }

    void Renderer::draw_circle_filled(
        Vec2f const center,
        int const radius,
        Color const color
    ) {
        DrawCircle(center.x, center.y, radius, to_raylib_color(color));
    }
}  // namespace gfx
