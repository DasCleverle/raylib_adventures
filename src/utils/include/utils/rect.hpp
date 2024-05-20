#pragma once

#include "concepts.hpp"
#include "vec2.hpp"

template<Numeric T>
struct Rect final {
    Vec2<T> origin;
    Vec2<T> size;

    constexpr Rect() = default;

    constexpr Rect(T const x, T const y, T const width, T const height)
        : origin{ x, y }, size{ width, height } {}

    constexpr Rect(Vec2<T> const origin, T const width, T const height)
        : origin{ origin }, size{ width, height } {}

    template<Numeric U>
    requires(not std::same_as<T, U>)
    constexpr explicit Rect(Rect<U> const& other)
        : origin{ static_cast<T>(other.origin.x),
                  static_cast<T>(other.origin.y) },
          size{ static_cast<T>(other.size.x), static_cast<T>(other.size.y) } {}

    [[nodiscard]] static constexpr Rect<T> unit() {
        return Rect{ 0, 0, 1, 1 };
    }
};

using RectI = Rect<int>;
using RectF = Rect<float>;
