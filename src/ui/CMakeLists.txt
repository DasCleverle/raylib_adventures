add_library(ui STATIC

    button.cpp
    checkbox.cpp
    column_layout.cpp
    event_dispatcher.cpp
    event_listener.cpp
    include/ui/button.hpp
    include/ui/checkbox.hpp
    include/ui/column_layout.hpp
    include/ui/event.hpp
    include/ui/event_dispatcher.hpp
    include/ui/event_listener.hpp
    include/ui/event_source.hpp
    include/ui/keycode.hpp
    include/ui/label.hpp
    include/ui/mouse_button.hpp
    include/ui/row_layout.hpp
    include/ui/utils.hpp
    include/ui/widget.hpp
    include/ui/widget_factory.hpp
    label.cpp
    row_layout.cpp
)

target_include_directories(ui PUBLIC include)

target_link_libraries(ui PRIVATE
    raylib
    tl::optional

    PUBLIC
    utils
    gfx)
