#pragma once

#include <string>
#include <vector>

namespace gfx {

    template<typename T>
    struct FontDefinition final {
        T font_type;
        std::string file_path;
        int font_size;
    };

    template<typename T>
    struct FontConfig final {
        std::vector<FontDefinition<T>> fonts;
        T default_font;
    };

}  // namespace gfx
