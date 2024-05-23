#pragma once

#include <memory>
#include "utils/vec2.hpp"

struct Font;

namespace gfx {
    class Renderer;
    class FontManager;

    class Font {
        friend class Renderer;
        friend class FontManager;

    private:
        struct Deleter {
            void operator()(::Font const* handle) const;
        };

        std::unique_ptr<::Font, Deleter> m_handle;

        Font(std::unique_ptr<::Font, Deleter> handle)
            : m_handle{ std::move(handle) } {}

    public:
        [[nodiscard]] Vec2f measure_text(
            char const* const text,
            float const font_size
        ) const;
    };
}  // namespace gfx
