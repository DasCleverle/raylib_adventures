#include <format>
#include <string>
#include <vector>

std::vector<std::string> split(std::string const& value, char delimiter);

template<typename I>
requires(std::same_as<typename std::iterator_traits<I>::value_type, std::string>)
std::string join(I begin, I end, char delimiter) {
    std::string result;

    if (begin == end) {
        return result;
    }

    for (auto it = begin; it != end; it++) {
        result.append(*it);

        if (std::next(it) != end) {
            result.push_back(delimiter);
        }
    }

    return result;
}

std::string utf32to8(std::u32string const& str);

std::string utf32to8(std::u32string_view const& str);

template<typename CharT>
struct std::formatter<std::u32string, CharT> {

    constexpr auto parse(std::format_parse_context& context) {
        return context.begin();
    }

    auto format(std::u32string const& str, std::format_context& context) const {
        return std::format_to(context.out(), "{}", utf32to8(str));
    }
};

template<typename CharT>
struct std::formatter<std::u32string_view, CharT> {

    constexpr auto parse(std::format_parse_context& context) {
        return context.begin();
    }

    auto format(std::u32string const& str, std::format_context& context) const {
        return std::format_to(context.out(), "{}", utf32to8(str));
    }
};
