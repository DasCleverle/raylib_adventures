#include "gfx/font.hpp"

#include <raylib.h>
#include <cstdio>
#include <format>
#include <vector>

namespace gfx {

    static std::array<std::pair<int, int>, 2> s_codepoint_ranges = {
        std::pair{0x20, 0x7e}, // ASCII characters
        std::pair{0xa1, 0xff}, // Latin supplement
    };

    void Font::Deleter::operator()(::Font const* handle) const {
        UnloadFont(*handle);
        delete handle;
    }

    Font::Font(std::string const& file_name, int font_size)
        : m_size{font_size} {

        std::vector<int> codepoints{};
        for (auto const [start, end] : s_codepoint_ranges) {
            for (int i = start; i < end; i++) {
                codepoints.push_back(i);
            }
        }

        ::Font const raylib_font =
            LoadFontEx(file_name.c_str(), font_size, codepoints.data(), codepoints.size());

        if (not IsFontReady(raylib_font) or raylib_font.texture.id == GetFontDefault().texture.id) {
            throw std::runtime_error{std::format("failed to load font '{}'", file_name)};
        }

        SetTextureFilter(raylib_font.texture, TEXTURE_FILTER_BILINEAR);

        m_handle = std::unique_ptr<::Font, Font::Deleter>{new ::Font{raylib_font}};
    }

    [[nodiscard]] Vec2i Font::measure_text(std::string const& text) const {
        auto const size = MeasureTextEx(*m_handle, text.c_str(), m_size, 0.0f);
        return Vec2i{
            static_cast<int>(std::ceil(size.x)),
            static_cast<int>(std::ceil(size.y)),
        };
    }

}  // namespace gfx
