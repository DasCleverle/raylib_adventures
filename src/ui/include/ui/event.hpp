#pragma once

#include "keycode.hpp"
#include "keystate.hpp"
#include "mouse_button.hpp"
#include "utils/vec2.hpp"

namespace ui {
    struct KeyboardEvent {
        KeyCode code;
        KeyState state;
    };

    struct MouseEvent {
        MouseButton button;
        KeyState state;
    };

    struct MouseMoveEvent {
        Vec2i origin;
        Vec2i target;
        Vec2i delta;
    };

    struct MouseWheelEvent {
        Vec2i delta;
    };
}  // namespace ui
