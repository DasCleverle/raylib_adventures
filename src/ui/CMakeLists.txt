add_library(ui STATIC
    button.cpp
    event_dispatcher.cpp
    label.cpp
    include/ui/button.hpp
    include/ui/event.hpp
    include/ui/event_dispatcher.hpp
    include/ui/event_listener.hpp
    include/ui/keycode.hpp
    include/ui/label.hpp
    include/ui/mouse_button.hpp
    include/ui/widget.hpp
)

target_include_directories(ui PUBLIC include)

target_link_libraries(ui PRIVATE
    raylib
    tl::optional

    PUBLIC
    utils
    gfx)
