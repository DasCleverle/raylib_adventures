#include "utils/strings.hpp"

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string const& value, char const delimiter) {
    std::stringstream stream{value};

    std::vector<std::string> result;
    std::string item;

    while (std::getline(stream, item, delimiter)) {
        if (item.size() == 0) {
            continue;
        }

        result.push_back(item);
    }

    return result;
}
