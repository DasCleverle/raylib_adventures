#include "gfx/font_manager.hpp"

#include <raylib.h>
#include <cstdio>
#include <memory>
#include <string>
#include <tl/optional.hpp>
#include <utility>

namespace gfx {

    tl::optional<Font const&> FontManager::load_font(
        std::string const& name,
        std::string const& file_name
    ) {
        auto const found = m_fonts.find(name);

        if (found != m_fonts.end()) {
            return *found->second;
        }

        ::Font const raylib_font = LoadFont(file_name.c_str());

        if (not IsFontReady(raylib_font)
            or raylib_font.texture.id == GetFontDefault().texture.id) {
            return tl::nullopt;
        }

        Font gfx_font{ std::unique_ptr<::Font, Font::Deleter>{
            new ::Font{ raylib_font } } };

        m_fonts.emplace(name, std::make_unique<Font>(std::move(gfx_font)));
        return *m_fonts.at(name);
    }

    tl::optional<Font const&> FontManager::get_font(std::string const& name
    ) const {
        auto const found = m_fonts.find(name);

        if (found == m_fonts.end()) {
            return tl::nullopt;
        }

        return *found->second;
    };

}  // namespace gfx
