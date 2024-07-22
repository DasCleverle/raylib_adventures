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
        DrawTextureRec(
            buffer.m_handle->texture,
            Rectangle{
                0,
                0,
                static_cast<float>(buffer.m_handle->texture.width),
                -static_cast<float>(buffer.m_handle->texture.height),
            },
            Vector2{
                static_cast<float>(position.x),
                static_cast<float>(position.y),
            },
            RayLibColor{0xff, 0xff, 0xff, 0xff}
        );
    }

    void Renderer::render_buffer(RenderBuffer const& buffer, Vec2i const position, RectI const section) {
        auto const height = buffer.m_handle->texture.height;

        DrawTextureRec(
            buffer.m_handle->texture,
            Rectangle{
                static_cast<float>(section.origin.x),
                static_cast<float>(-section.origin.y + (height - section.size.y)),
                static_cast<float>(section.size.x),
                static_cast<float>(-height + (height - section.size.y)),
            },
            Vector2{
                static_cast<float>(position.x),
                static_cast<float>(position.y),
            },
            RayLibColor{0xff, 0xff, 0xff, 0xff}
        );
    }

    void Renderer::with_shader(Shader const& shader, std::function<void(Renderer&)> render) {
        RendererBase::with_shader(shader, [this, render](auto& _) { render(*this); });
    }

}  // namespace gfx
