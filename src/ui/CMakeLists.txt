add_library(ui STATIC

    button.cpp
    checkbox.cpp
    column_layout.cpp
    dropdown.cpp
    event_dispatcher.cpp
    event_listener.cpp
    include/ui/button.hpp
    include/ui/checkbox.hpp
    include/ui/column_layout.hpp
    include/ui/dropdown.hpp
    include/ui/event.hpp
    include/ui/event_dispatcher.hpp
    include/ui/event_listener.hpp
    include/ui/event_source.hpp
    include/ui/keycode.hpp
    include/ui/label.hpp
    include/ui/mouse.hpp
    include/ui/mouse_button.hpp
    include/ui/row_layout.hpp
    include/ui/scene.hpp
    include/ui/scene_stack.hpp
    include/ui/textbox.hpp
    include/ui/ui_scene.hpp
    include/ui/utils.hpp
    include/ui/widget.hpp
    include/ui/widget_factory.hpp
    label.cpp
    mouse.cpp
    row_layout.cpp
    scene_stack.cpp
    textbox.cpp
    ui_scene.cpp

)

target_include_directories(ui PUBLIC include)

target_link_libraries(ui PRIVATE
    raylib
    tl::optional

    PUBLIC
    utils
    gfx)
