#pragma once

#include <cmath>
#include <concepts>
#include <format>
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

    template<std::integral U>
    requires(not std::same_as<T, U> and std::floating_point<T>)
    constexpr Vec2(U x, U y)
        : x{static_cast<T>(x)}, y{static_cast<T>(y)} {}

    template<std::floating_point U>
    requires(not std::same_as<T, U> and std::integral<T>)
    constexpr Vec2(U x, U y)
        : x{static_cast<T>(std::floor(x))}, y{static_cast<T>(std::floor(y))} {}

    constexpr Vec2()
        : x{}, y{} {}

    template<std::floating_point U>
    requires(not std::same_as<T, U> and std::integral<T>)
    constexpr Vec2(Vec2<U> const other)
        : Vec2{other.x, other.y} {}

    template<std::integral U>
    requires(not std::same_as<T, U> and std::floating_point<T>)
    constexpr Vec2(Vec2<U> const other)
        : Vec2{other.x, other.y} {}

    [[nodiscard]] constexpr Vec2 hadamard_product(Vec2 const other) const {
        return Vec2{x * other.x, y * other.y};
    }

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

    template<std::floating_point U>
    requires(not std::same_as<T, U> and std::integral<T>)
    constexpr Vec2<U> operator*(U const scalar) const {
        return Vec2(static_cast<U>(x) * scalar, static_cast<U>(y) * scalar);
    }

    template<std::floating_point U>
    requires(not std::same_as<T, U> and std::integral<T>)
    constexpr Vec2<U> operator/(U const scalar) const {
        return Vec2(static_cast<U>(x) / scalar, static_cast<U>(y) / scalar);
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

inline Vec2f operator+(Vec2f const a, Vec2i const b) {
    return Vec2{a.x + b.x, a.y + b.y};
}

inline Vec2f operator+(Vec2i const a, Vec2f const b) {
    return Vec2{a.x + b.x, a.y + b.y};
}

inline Vec2f operator+=(Vec2f a, Vec2i const b) {
    a.x += b.x;
    a.y += b.y;

    return a;
}

inline Vec2i operator+=(Vec2i a, Vec2f const b) {
    a.x += b.x;
    a.y += b.y;

    return a;
}

inline Vec2f operator-(Vec2f const a, Vec2i const b) {
    return Vec2{a.x - b.x, a.y - b.y};
}

inline Vec2f operator-(Vec2i const a, Vec2f const b) {
    return Vec2{a.x - b.x, a.y - b.y};
}

inline Vec2f operator-=(Vec2f a, Vec2i const b) {
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

inline Vec2i operator-=(Vec2i a, Vec2f const b) {
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

template<typename T, typename CharT>
struct std::formatter<Vec2<T>, CharT> {

    constexpr auto parse(std::format_parse_context& context) {
        return context.begin();
    }

    auto format(Vec2<T> const& vec, std::format_context& context) const {
        return std::format_to(context.out(), "Vec{{ {}, {} }}", vec.x, vec.y);
    }
};
