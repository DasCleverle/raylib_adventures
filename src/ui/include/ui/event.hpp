#pragma once

#include <variant>

#include "keycode.hpp"
#include "keystate.hpp"
#include "mouse_button.hpp"
#include "utils/vec2.hpp"

namespace ui {
    struct KeyboardEvent final {
        KeyCode code;
        KeyState state;
    };

    struct TypedEvent final {
        char32_t utf8_codepoint;
    };

    struct MouseEvent final {
        MouseButton button;
        KeyState state;
        Vec2i position;
    };

    struct MouseMoveEvent final {
        Vec2i origin;
        Vec2i target;
        Vec2i delta;
    };

    struct MouseWheelEvent final {
        Vec2i position;
        Vec2i delta;
    };

    class Button;
    class Checkbox;

    struct ClickEvent final {
        Button* button;
        MouseEvent event;
    };

    struct CheckedEvent final {
        Checkbox* checkbox;
        bool checked;
        MouseEvent event;
    };

    using Event =
        std::variant<KeyboardEvent, TypedEvent, MouseEvent, MouseMoveEvent, MouseWheelEvent, ClickEvent, CheckedEvent>;
}  // namespace ui
