#include "gfx/render_buffer.hpp"

#include <raylib.h>

namespace gfx {

    void RenderBuffer::Deleter::operator()(RenderTexture2D const* handle) const {
        UnloadRenderTexture(*handle);
        delete handle;
    }

    RenderBuffer::RenderBuffer(Vec2i size)
        : m_renderer{BufferRenderer{}} {
        resize(size);
    }

    RenderBuffer::RenderBuffer()
        : m_handle{nullptr} {}

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

    void RenderBuffer::render_to(std::function<void(BufferRenderer&)> render) {
        if (m_handle == nullptr) {
            return;
        }

        m_last_render_to = render;

        BeginTextureMode(*m_handle);
        render(m_renderer);
        EndTextureMode();
    }

    void RenderBuffer::resize(Vec2i new_size) {
        RenderTexture2D const texture = LoadRenderTexture(new_size.x, new_size.y);

        m_size = new_size;
        m_handle = std::unique_ptr<RenderTexture2D, RenderBuffer::Deleter>{
            new RenderTexture2D{texture},
        };

        render_to(m_last_render_to);
    }

}  // namespace gfx
