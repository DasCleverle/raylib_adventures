#pragma once

#include <functional>
#include "gfx/renderer_base.hpp"
#include "utils/vec2.hpp"

struct RenderTexture;

namespace gfx {

    class Renderer;
    class Shader;

    class BufferRenderer final : public RendererBase {
    public:
        BufferRenderer() = default;
        BufferRenderer(BufferRenderer const&) = delete;
        BufferRenderer(BufferRenderer&&) = delete;
        BufferRenderer& operator=(BufferRenderer const&) = delete;
        BufferRenderer& operator=(BufferRenderer&&) = delete;
        ~BufferRenderer() = default;

        void with_shader(Shader const& shader, std::function<void(BufferRenderer&)> render);
    };

    class RenderBuffer final {
        friend class Renderer;
        friend class Shader;

    private:

        struct Deleter {
            void operator()(::RenderTexture const* handle) const;
        };

        std::function<void(BufferRenderer&)> m_last_render_to = [](BufferRenderer&) {
        };
        Vec2i m_size;
        std::unique_ptr<::RenderTexture, Deleter> m_handle;
        BufferRenderer m_renderer;

    public:
        RenderBuffer();
        RenderBuffer(Vec2i size);

        RenderBuffer(RenderBuffer const&) = delete;
        RenderBuffer& operator=(RenderBuffer const&) = delete;
        RenderBuffer& operator=(RenderBuffer&&);
        RenderBuffer(RenderBuffer&&);
        ~RenderBuffer() = default;

        void render_to(std::function<void(BufferRenderer&)> render);

        void resize(Vec2i new_size);

        [[nodiscard]] Vec2i size() const {
            return m_size;
        }
    };

}  // namespace gfx
