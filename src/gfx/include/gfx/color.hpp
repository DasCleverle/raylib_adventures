#pragma once

#include <cstdint>

namespace gfx {
    struct Color final {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a;

        constexpr Color() {}

        constexpr Color(
            std::uint8_t r,
            std::uint8_t g,
            std::uint8_t b,
            std::uint8_t a
        )
            : r{ r }, g{ g }, b{ b }, a{ a } {}
    };

    struct Colors {  // clang-format off
        static inline constexpr Color LightGray  { 200, 200, 200, 255 };
        static inline constexpr Color Gray       { 130, 130, 130, 255 };
        static inline constexpr Color DarkGray   { 80, 80, 80, 255 };
        static inline constexpr Color Yellow     { 253, 249, 0, 255 };
        static inline constexpr Color Gold       { 255, 203, 0, 255 };
        static inline constexpr Color Orange     { 255, 161, 0, 255 };
        static inline constexpr Color Pink       { 255, 109, 194, 255 };
        static inline constexpr Color Red        { 230, 41, 55, 255 };
        static inline constexpr Color Maroon     { 190, 33, 55, 255 };
        static inline constexpr Color Green      { 0, 228, 48, 255 };
        static inline constexpr Color Lime       { 0, 158, 47, 255 };
        static inline constexpr Color DarkGreen  { 0, 117, 44, 255 };
        static inline constexpr Color SkyBlue    { 102, 191, 255, 255 };
        static inline constexpr Color Blue       { 0, 121, 241, 255 };
        static inline constexpr Color DarkBlue   { 0, 82, 172, 255 };
        static inline constexpr Color Purple     { 200, 122, 255, 255 };
        static inline constexpr Color Violet     { 135, 60, 190, 255 };
        static inline constexpr Color DarkPurple { 112, 31, 126, 255 };
        static inline constexpr Color Beige      { 211, 176, 131, 255 };
        static inline constexpr Color Brown      { 127, 106, 79, 255 };
        static inline constexpr Color DarkBrown  { 76, 63, 47, 255 };

        static inline constexpr Color White      { 255, 255, 255, 255 };
        static inline constexpr Color Black      { 0, 0, 0, 255 };
        static inline constexpr Color Blank      { 0, 0, 0, 0 };
        static inline constexpr Color Magenta    { 255, 0, 255, 255 };
        static inline constexpr Color RayWhite   { 245, 245, 245, 255 };
    };  // clang-format on
}  // namespace gfx
