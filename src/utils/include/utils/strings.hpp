#include <cstddef>
#include <cstdint>
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

std::size_t insert_utf8_codepoint(std::string& target, std::size_t index, std::uint32_t codepoint);

std::size_t erase_utf8_codepoint(std::string& target, std::size_t index);

std::size_t find_utf8_boundary(std::string const& str, std::size_t index);

std::size_t rfind_utf8_boundary(std::string const& str, std::size_t index);
