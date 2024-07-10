#include "utils/strings.hpp"

#include <iterator>
#include <sstream>
#include <string>
#include <vector>

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

std::size_t insert_utf8_codepoint(
    std::string& target,
    std::size_t const index,
    std::uint32_t const codepoint
) {
    if (target.size() < index) {
        throw std::runtime_error{"index must be less than string size"};
    }

    auto it = target.begin();
    std::advance(it, index);

    if (codepoint <= 0x7F) {
        // 1-byte sequence: 0xxxxxxx
        target.insert(it, static_cast<char>(codepoint));
        return 1;
    }

    if (codepoint <= 0x7FF) {
        // 2-byte sequence: 110xxxxx 10xxxxxx
        target.insert(it, static_cast<char>(0xC0 | (codepoint >> 6)));
        target.insert(++it, static_cast<char>(0x80 | (codepoint & 0x3F)));
        return 2;
    }

    if (codepoint <= 0xFFFF) {
        // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
        target.insert(it, static_cast<char>(0xE0 | (codepoint >> 12)));
        target.insert(++it, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
        target.insert(++it, static_cast<char>(0x80 | (codepoint & 0x3F)));
        return 3;
    }

    if (codepoint <= 0x10FFFF) {
        // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        target.insert(it, static_cast<char>(0xF0 | (codepoint >> 18)));
        target.insert(++it, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F)));
        target.insert(++it, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
        target.insert(++it, static_cast<char>(0x80 | (codepoint & 0x3F)));
        return 4;
    }

    throw std::invalid_argument("Invalid UTF-8 codepoint");
}

std::size_t erase_utf8_codepoint(std::string& target, std::size_t const index) {
    auto begin = rfind_utf8_boundary(target, index);
    auto end = find_utf8_boundary(target, index);

    if (end == begin) {
        end++;
    }

    target.erase(begin, end - begin);
    return end - begin;
}

std::size_t find_utf8_boundary(std::string const& str, std::size_t index) {
    if (str.size() < index) {
        throw new std::runtime_error{"index must be less than string size"};
    }

    if (index == 0) {
        return 0;
    }

    unsigned char c = str[index];

    // Insid of multibyte utf8 sequences all bytes start with a one bit (0x80)
    while ((c & 0x80) == 0x80) {
        // Multibyte utf8 sequences start with at least two bit (0xC0)
        if ((c & 0xC0) == 0xC0) {
            return index;
        }

        ++index;

        if (index == str.size()) {
            return index;
        }

        c = str[index];
    }

    return index;
}

std::size_t rfind_utf8_boundary(std::string const& str, std::size_t index) {
    if (str.size() <= index) {
        throw new std::runtime_error{"index must be less than string size"};
    }

    if (index == 0) {
        return 0;
    }

    unsigned char c = str[index];

    while ((c & 0x80) == 0x80) {
        if ((c & 0xC0) == 0xC0) {
            return index;
        }

        --index;

        if (index == 0) {
            return index;
        }

        c = str[index];
    }

    return index;
}
