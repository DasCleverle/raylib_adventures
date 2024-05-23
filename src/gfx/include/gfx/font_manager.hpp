#pragma once

#include <memory>
#include <tl/optional.hpp>
#include <unordered_map>

#include "font.hpp"
#include "font_config.hpp"

namespace gfx {

    template<typename T>
    class FontManager {
    private:
        std::unordered_map<T, std::unique_ptr<Font>> m_fonts;
        Font const* m_default_font;

    public:
        FontManager(FontConfig<T> const& config) {
            for (auto const& definition : config.fonts) {
                m_fonts.emplace(
                    definition.font_type,
                    std::make_unique<Font>(
                        Font(definition.file_path, definition.font_size)
                    )
                );
            }

            m_default_font = m_fonts.at(config.default_font).get();
        }

        FontManager(FontManager const&) = delete;
        FontManager(FontManager&&) = delete;
        FontManager& operator=(FontManager const&) = delete;
        FontManager& operator=(FontManager&&) = delete;

        Font const& get_font(T font_type) const {
            return *m_fonts.at(font_type);
        }

        Font const& default_font() const {
            return *m_default_font;
        }
    };

}  // namespace gfx
