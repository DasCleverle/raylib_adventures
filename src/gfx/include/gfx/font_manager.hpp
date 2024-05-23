#pragma once

#include <memory>
#include <string>
#include <tl/optional.hpp>
#include <unordered_map>

#include "font.hpp"

namespace gfx {
    class Window;

    class FontManager {
        friend class Window;

    private:
        std::unordered_map<std::string, std::unique_ptr<Font>> m_fonts;

        FontManager() = default;

    public:
        FontManager(FontManager const&) = delete;
        FontManager(FontManager&&) = delete;
        FontManager& operator=(FontManager const&) = delete;
        FontManager& operator=(FontManager&&) = delete;
        ~FontManager() = default;

        tl::optional<Font const&> load_font(
            std::string const& name,
            std::string const& file_name
        );
        tl::optional<Font const&> get_font(std::string const& name) const;
    };

}  // namespace gfx
