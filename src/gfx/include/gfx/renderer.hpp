#pragma once

#include "utils/vec2.hpp"

#include "font.hpp"
#include "renderer_base.hpp"
#include "window.hpp"

namespace gfx {
    class RenderBuffer;

    class Renderer final : public RendererBase {
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

        void draw_fps(Vec2i position);

        void render_buffer(RenderBuffer const& buffer, Vec2i position);

        void render_buffer(RenderBuffer const& buffer, Vec2i position, RectI section);
    };
}  // namespace gfx
