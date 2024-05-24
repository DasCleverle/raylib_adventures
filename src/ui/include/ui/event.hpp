#pragma once

#include "keycode.hpp"
#include "keystate.hpp"
#include "mouse_button.hpp"

namespace ui {
    struct KeyboardEvent {
        KeyCode code;
        KeyState state;
    };

    struct MouseEvent {
        MouseButton button;
        KeyState state;
    };
}  // namespace ui
