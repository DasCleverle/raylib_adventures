#pragma once

#include <memory>
#include "utils/vec2.hpp"

struct Font;

namespace gfx {

    class Renderer;

    template<typename T>
    class FontManager;

    class Font final {
        friend class Renderer;

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
        [[nodiscard]] Vec2i measure_text(char const* const text) const;
    };
}  // namespace gfx
