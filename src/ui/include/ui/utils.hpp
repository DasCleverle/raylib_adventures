#pragma once

#include <format>
#include <string>

namespace ui {
    template<typename T>
    std::string get_next_id(std::string_view prefix) {
        static int id = 0;
        return std::format("{}_{}", prefix, id++);
    }
}  // namespace ui
