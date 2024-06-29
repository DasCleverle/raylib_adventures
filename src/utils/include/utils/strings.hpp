#include <string>
#include <vector>

std::vector<std::string> split(std::string const& value, char const delimiter);

template<typename I>
requires(std::same_as<typename std::iterator_traits<I>::value_type, std::string>)
std::string join(I begin, I end, char const delimiter) {
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
