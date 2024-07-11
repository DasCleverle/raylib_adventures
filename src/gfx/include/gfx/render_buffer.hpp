#pragma once

#include <functional>
#include "gfx/renderer_base.hpp"
#include "utils/vec2.hpp"

struct RenderTexture;

namespace gfx {

    class Renderer;

    class BufferRenderer final : public RendererBase {
    public:
        BufferRenderer() = default;
        BufferRenderer(BufferRenderer const&) = delete;
        BufferRenderer(BufferRenderer&&) = delete;
        BufferRenderer& operator=(BufferRenderer const&) = delete;
        BufferRenderer& operator=(BufferRenderer&&) = delete;
        ~BufferRenderer() = default;
    };

    class RenderBuffer final {
        friend class Renderer;

    private:

        struct Deleter {
            void operator()(::RenderTexture const* handle) const;
        };

        std::unique_ptr<::RenderTexture, Deleter> m_handle;
        BufferRenderer m_renderer;

    public:
        RenderBuffer(Vec2i size);
        ~RenderBuffer();

        RenderBuffer(RenderBuffer const&) = delete;
        RenderBuffer& operator=(RenderBuffer const&) = delete;
        RenderBuffer& operator=(RenderBuffer&&);
        RenderBuffer(RenderBuffer&&);

        void render_to(std::function<void(BufferRenderer const&)> render) const;
    };

}  // namespace gfx
