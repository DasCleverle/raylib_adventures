#include "gfx/render_buffer.hpp"

#include <raylib.h>

namespace gfx {

    void RenderBuffer::Deleter::operator()(RenderTexture2D const* handle) const {
        UnloadRenderTexture(*handle);
        delete handle;
    }

    RenderBuffer::RenderBuffer(Vec2i size)
        : m_renderer{BufferRenderer{}} {
        RenderTexture2D const texture = LoadRenderTexture(size.x, size.y);

        m_handle = std::unique_ptr<RenderTexture2D, RenderBuffer::Deleter>{
            new RenderTexture2D{texture},
        };
    }

    RenderBuffer& RenderBuffer::operator=(RenderBuffer&& other) {
        if (&other == this) {
            return *this;
        }

        using std::swap;
        swap(m_handle, other.m_handle);

        return *this;
    }

    RenderBuffer::RenderBuffer(RenderBuffer&& other)
        : m_handle{std::move(other.m_handle)}, m_renderer{BufferRenderer{}} {}

    void RenderBuffer::render_to(std::function<void(BufferRenderer const&)> render) const {
        BeginTextureMode(*m_handle);
        render(m_renderer);
        EndTextureMode();
    }

}  // namespace gfx
