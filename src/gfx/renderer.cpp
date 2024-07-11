#include "gfx/renderer.hpp"
#include "gfx/render_buffer.hpp"

#include <raylib.h>

using MyColor = gfx::Color;
using RayLibColor = Color;

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

    void Renderer::draw_fps(Vec2i const position) {
        DrawFPS(position.x, position.y);
    }

    void Renderer::render_buffer(RenderBuffer const& buffer, Vec2i const position) {
        DrawTexture(buffer.m_handle->texture, position.x, position.y, RayLibColor{0, 0, 0, 0});
    }

    void Renderer::render_buffer(RenderBuffer const& buffer, Vec2i const position, RectI const section) {
        DrawTextureRec(
            buffer.m_handle->texture,
            Rectangle{
                static_cast<float>(section.origin.x),
                static_cast<float>(section.origin.y),
                static_cast<float>(section.size.x),
                static_cast<float>(section.size.y),
            },
            Vector2{
                static_cast<float>(position.x),
                static_cast<float>(position.y),
            },
            RayLibColor{0, 0, 0, 0}
        );
    }

}  // namespace gfx
