#include "gfx/font.hpp"

#include <raylib.h>
#include <cstdio>
#include <format>

namespace gfx {

    void Font::Deleter::operator()(::Font const* handle) const {
        UnloadFont(*handle);
        delete handle;
    }

    Font::Font(std::string const& file_name, int font_size)
        : m_size{ font_size } {
        ::Font const raylib_font = LoadFont(file_name.c_str());

        if (not IsFontReady(raylib_font)
            or raylib_font.texture.id == GetFontDefault().texture.id) {
            throw std::runtime_error{
                std::format("failed to load font '{}'", file_name)
            };
        }

        m_handle =
            std::unique_ptr<::Font, Font::Deleter>{ new ::Font{ raylib_font } };
    }

    [[nodiscard]] Vec2f Font::measure_text(char const* const text) const {
        auto const size = MeasureTextEx(*m_handle, text, m_size, 0.0);
        return Vec2f{ size.x, size.y };
    }

}  // namespace gfx
