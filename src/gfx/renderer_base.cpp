#include "gfx/renderer_base.hpp"

#include <raylib.h>

using MyColor = gfx::Color;
using RayLibColor = Color;

template<typename T>
static inline constexpr Vector2 to_raylib_vector(Vec2<T> vector) {
    return Vector2{
        static_cast<float>(vector.x),
        static_cast<float>(vector.y),
    };
}

template<typename T>
static inline constexpr Rectangle to_raylib_rect(Rect<T> rect) {
    return Rectangle{
        static_cast<float>(rect.origin.x),
        static_cast<float>(rect.origin.y),
        static_cast<float>(rect.size.x),
        static_cast<float>(rect.size.y),
    };
}

static inline constexpr RayLibColor to_raylib_color(MyColor color) {
    return {color.r, color.g, color.b, color.a};
}

namespace gfx {

    void RendererBase::clear_background(MyColor color) {
        ClearBackground(to_raylib_color(color));
    }

    void RendererBase::draw_text(
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

    void RendererBase::draw_text(
        Font const& font,
        std::u32string_view text,
        Vec2i const position,
        Color const color
    ) {
        DrawTextCodepoints(
            *font.m_handle,
            reinterpret_cast<int const*>(text.data()),
            text.size(),
            {static_cast<float>(position.x), static_cast<float>(position.y)},
            font.m_size,
            0,
            to_raylib_color(color)
        );
    }

    void RendererBase::draw_rect_filled(RectI const rect, Color const color) {
        DrawRectangle(rect.origin.x, rect.origin.y, rect.size.x, rect.size.y, to_raylib_color(color));
    }

    void RendererBase::draw_rect_outline(RectI const rect, int const thickness, Color const color) {
        DrawRectangleLinesEx(
            to_raylib_rect(rect),
            static_cast<float>(thickness),
            to_raylib_color(color)
        );
    }

    void RendererBase::draw_circle_filled(Vec2i const center, int const radius, Color const color) {
        DrawCircle(center.x, center.y, radius, to_raylib_color(color));
    }

    void RendererBase::draw_circle_outline(Vec2i const center, int const radius, Color const color) {
        DrawCircleLines(center.x, center.y, radius, to_raylib_color(color));
    }

    void RendererBase::draw_triangle_filled(Vec2i vertex_0, Vec2i vertex_1, Vec2i vertex_2, Color color) {
        DrawTriangle(
            to_raylib_vector(vertex_0),
            to_raylib_vector(vertex_1),
            to_raylib_vector(vertex_2),
            to_raylib_color(color)
        );
    }

    void RendererBase::draw_line(Vec2i from, Vec2i to, int const thickness, Color const color) {
        DrawLineEx(to_raylib_vector(from), to_raylib_vector(to), thickness, to_raylib_color(color));
    }

    void RendererBase::with_shader(Shader const& shader, std::function<void(RendererBase&)> render) {
        BeginShaderMode(*shader.m_handle);
        render(*this);
        EndShaderMode();
    }

}  // namespace gfx
