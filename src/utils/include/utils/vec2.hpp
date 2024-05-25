#pragma once

#include "concepts.hpp"

template<Numeric T>
struct Vec2 final {
    T x;
    T y;

    static constexpr Vec2<T> zero() {
        return Vec2<T>{};
    }

    static constexpr Vec2<T> unit() {
        return Vec2<T>{static_cast<T>(1), static_cast<T>(1)};
    }

    constexpr Vec2(T x, T y)
        : x{x}, y{y} {}

    constexpr Vec2()
        : x{}, y{} {}

    template<Numeric U>
    requires(not std::same_as<T, U>)
    constexpr explicit Vec2(Vec2<U> const other)
        : x{static_cast<T>(other.x)}, y{static_cast<T>(other.y)} {}

    constexpr Vec2 operator+(Vec2 const& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    constexpr Vec2 operator-(Vec2 const& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    constexpr Vec2 operator*(T const scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    constexpr Vec2 operator/(T const scalar) const {
        return Vec2(x / scalar, y / scalar);
    }

    template<Numeric U>
    requires(not std::same_as<T, U>)
    constexpr Vec2 operator*(U const scalar) const {
        return Vec2(x * static_cast<T>(scalar), y * static_cast<T>(scalar));
    }

    template<Numeric U>
    requires(not std::same_as<T, U>)
    constexpr Vec2 operator/(U const scalar) const {
        return Vec2(x / static_cast<T>(scalar), y / static_cast<T>(scalar));
    }

    constexpr Vec2& operator+=(Vec2 const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Vec2& operator-=(Vec2 const& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr Vec2& operator*=(T const scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr Vec2& operator/=(T const scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    template<Numeric U>
    requires(not std::same_as<T, U>)
    constexpr Vec2& operator*=(U const scalar) {
        x *= static_cast<T>(scalar);
        y *= static_cast<T>(scalar);
        return *this;
    }

    template<Numeric U>
    requires(not std::same_as<T, U>)
    constexpr Vec2& operator/=(U const scalar) {
        x /= static_cast<T>(scalar);
        y /= static_cast<T>(scalar);
        return *this;
    }

    constexpr bool operator==(Vec2 const& other) const {
        return x == other.x && y == other.y;
    }

    constexpr bool operator!=(Vec2 const& other) const {
        return !(*this == other);
    }
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
