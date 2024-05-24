add_library(ui STATIC
    include/ui/event_dispatcher.hpp
    event_dispatcher.cpp
)

target_include_directories(ui PUBLIC include)

target_link_libraries(ui PRIVATE
    raylib

    PUBLIC
    utils)
