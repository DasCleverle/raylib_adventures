add_library(utils INTERFACE
    include/utils/concepts.hpp
    include/utils/rect.hpp
    include/utils/unique_value.hpp
    include/utils/vec2.hpp
)

target_include_directories(utils INTERFACE include)
