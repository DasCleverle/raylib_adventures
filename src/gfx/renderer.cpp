#include <gfx/renderer.hpp>

#include <raylib.h>

using MyColor = gfx::Color;
using RayLibColor = Color;

RayLibColor to_raylib_color(MyColor color) {
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
        Vec2i position,
        int size,
        Color color
    ) {
        DrawText(text, position.x, position.y, size, to_raylib_color(color));
    }

    [[nodiscard]] int
        Renderer::measure_text(char const* const text, int const size) {
        return MeasureText(text, size);
    }

    void Renderer::draw_rect_filled(RectI const rect, Color const color) {
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

}  // namespace gfx
