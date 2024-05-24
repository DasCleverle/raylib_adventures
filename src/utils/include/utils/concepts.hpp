#pragma once

#include <concepts>

template<typename T>
concept Numeric = std::integral<T> or std::floating_point<T>;

template<typename T, typename... Args>
concept OneOf = (std::same_as<T, Args> || ...);
