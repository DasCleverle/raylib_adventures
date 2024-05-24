#pragma once

#include <variant>

#include "keycode.hpp"
#include "keystate.hpp"
#include "mouse_button.hpp"
#include "utils/concepts.hpp"

namespace ui {
    enum class EventType { KeyboardEvent, MouseEvent };

    struct KeyboardEvent {
        static constexpr EventType type = EventType::KeyboardEvent;

        KeyCode code;
        KeyState state;
    };

    struct MouseEvent {
        static constexpr EventType type = EventType::KeyboardEvent;

        MouseButton button;
        KeyState state;
    };

    using Event = std::variant<KeyboardEvent, MouseEvent>;

    template<typename T>
    concept IsEvent = OneOf<T, KeyboardEvent, MouseEvent>;
}  // namespace ui
