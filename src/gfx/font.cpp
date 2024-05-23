#include "gfx/font.hpp"

#include <raylib.h>
#include <cstdio>

namespace gfx {

    void Font::Deleter::operator()(::Font const* handle) const {
        UnloadFont(*handle);
        delete handle;
    }

    [[nodiscard]] Vec2f Font::measure_text(
        char const* const text,
        float const font_size
    ) const {
        auto const size = MeasureTextEx(*m_handle, text, font_size, 0.0);
        return Vec2f{ size.x, size.y };
    }

}  // namespace gfx
