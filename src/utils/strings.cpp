#include "utils/strings.hpp"

#include <sstream>
#include <string>
#include <vector>

#include <utf8.h>

std::vector<std::string> split(std::string const& value, char const delimiter) {
    std::stringstream stream{value};

    std::vector<std::string> target;
    std::string item;

    while (std::getline(stream, item, delimiter)) {
        if (item.size() == 0) {
            continue;
        }

        target.push_back(item);
    }

    return target;
}

std::string utf32to8(std::u32string const& str) {
    return utf8::utf32to8(str);
}

std::string utf32to8(std::u32string_view const& str) {
    std::string result;
    utf8::utf32to8(str.begin(), str.end(), std::back_inserter(result));
    return result;
}
