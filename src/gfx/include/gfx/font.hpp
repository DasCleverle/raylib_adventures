#pragma once

#include <memory>
#include "utils/vec2.hpp"

struct Font;

namespace gfx {

    class RendererBase;

    template<typename T>
    class FontManager;

    class Font final {
        friend class RendererBase;

        template<typename T>
        friend class FontManager;

    private:
        struct Deleter {
            void operator()(::Font const* handle) const;
        };

        std::unique_ptr<::Font, Deleter> m_handle;
        int m_size;

        Font(std::string const& file_name, int font_size);

    public:
        [[nodiscard]] int size() const {
            return m_size;
        }

        [[nodiscard]] Vec2i measure_text(std::string const& text) const;
        [[nodiscard]] Vec2i measure_text(std::u32string_view text) const;
    };
}  // namespace gfx
