#pragma once

#include <cmath>
#include <concepts>
#include <format>
#include "concepts.hpp"
#include "vec2.hpp"

template<Numeric T>
struct Rect final {
    Vec2<T> origin;
    Vec2<T> size;

    constexpr Rect() = default;

    constexpr Rect(T const x, T const y, T const width, T const height)
        : origin{x, y}, size{width, height} {}

    constexpr Rect(Vec2<T> const origin, T const width, T const height)
        : origin{origin}, size{width, height} {}

    constexpr Rect(Vec2<T> const origin, Vec2<T> const size)
        : origin{origin}, size{size} {}

    template<std::floating_point U>
    requires(not std::same_as<T, U> and std::integral<T>)
    constexpr Rect(Rect<U> const& other)
        : origin{static_cast<T>(std::floor(other.origin.x)), static_cast<T>(std::floor(other.origin.y))},
          size{static_cast<T>(std::ceil(other.size.x)), static_cast<T>(std::ceil(other.size.y))} {}

    template<std::integral U>
    requires(not std::same_as<T, U> and std::floating_point<T>)
    constexpr Rect(Rect<U> const& other)
        : origin{static_cast<T>(other.origin.x), static_cast<T>(other.origin.y)},
          size{static_cast<T>(other.size.x), static_cast<T>(other.size.y)} {}

    [[nodiscard]] static constexpr Rect unit() {
        return Rect{0, 0, 1, 1};
    }

    [[nodiscard]] constexpr Rect to_absolute(Rect const reference) const {
        return Rect{
            reference.origin + reference.size.hadamard_product(origin),
            reference.size.hadamard_product(size),
        };
    }

    [[nodiscard]] constexpr Vec2<T> center() const {
        return Vec2{
            origin.x + size.x / 2,
            origin.y + size.y / 2,
        };
    }

    [[nodiscard]] constexpr bool contains(Vec2<T> const position) const {
        return position.x >= origin.x and position.y >= origin.y and position.x <= origin.x + size.x
               and position.y <= origin.y + size.y;
    }

    [[nodiscard]] constexpr Rect scale_from_center(float factor) const {
        if (factor == 1) {
            return Rect{*this};
        }

        float sign = factor > 1 ? -1 : 1;
        Vec2f scaled_size = size * factor;
        Vec2f scaled_origin = origin + ((size - scaled_size) / 2.0f) * sign;

        return Rect{scaled_origin, scaled_size};
    }
};

using RectI = Rect<int>;
using RectF = Rect<float>;

template<typename T, typename CharT>
struct std::formatter<Rect<T>, CharT> {

    constexpr auto parse(std::format_parse_context& context) {
        return context.begin();
    }

    auto format(Rect<T> const& rect, std::format_context& context) const {
        return std::format_to(
            context.out(),
            "Rect{{ {}, {}, {}, {} }}",
            rect.origin.x,
            rect.origin.y,
            rect.size.x,
            rect.size.y
        );
    }
};
