add_library(utils STATIC
    include/utils/concepts.hpp
    include/utils/rect.hpp
    include/utils/unique_value.hpp
    include/utils/strings.hpp
    include/utils/vec2.hpp
    strings.cpp
)

target_include_directories(utils PUBLIC include)

target_link_libraries(utils PRIVATE utf8cpp)
