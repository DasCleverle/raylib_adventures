#include "ui/event_dispatcher.hpp"

#include <raylib.h>
#include <vector>

#include "ui/event.hpp"
#include "ui/keycode.hpp"
#include "ui/keystate.hpp"
#include "utils/vec2.hpp"

namespace ui {

    void EventDispatcher::poll_keyboard() {
        for (auto it = m_pressed_keys.begin(); it != m_pressed_keys.end();) {
            int key = *it;

            if (IsKeyReleased(key)) {
                publish(KeyboardEvent{ static_cast<KeyCode>(key),
                                       KeyState::Released });
                it = m_pressed_keys.erase(it);
            }
            else {
                it++;
            }
        }

        int key;
        while ((key = GetKeyPressed()) != 0) {
            m_pressed_keys.push_back(key);
            publish(KeyboardEvent{ static_cast<KeyCode>(key),
                                   KeyState::Pressed });
        }
    }

    void EventDispatcher::poll_mouse() {
        for (auto it = m_mouse_buttons.begin(); it != m_mouse_buttons.end();) {
            int mouse_button = *it;

            if (IsMouseButtonReleased(mouse_button)) {
                publish(MouseEvent{ static_cast<MouseButton>(mouse_button),
                                    KeyState::Released });
                it = m_mouse_buttons.erase(it);
            }
            else {
                it++;
            }
        }

        check_mouse_button(MOUSE_BUTTON_LEFT);
        check_mouse_button(MOUSE_BUTTON_RIGHT);
        check_mouse_button(MOUSE_BUTTON_MIDDLE);
        check_mouse_button(MOUSE_BUTTON_SIDE);
        check_mouse_button(MOUSE_BUTTON_EXTRA);
        check_mouse_button(MOUSE_BUTTON_FORWARD);
        check_mouse_button(MOUSE_BUTTON_BACK);
    }

    void EventDispatcher::check_mouse_button(int mouse_button) {
        if (IsMouseButtonPressed(mouse_button)) {
            m_mouse_buttons.push_back(mouse_button);
            publish(MouseEvent{ static_cast<MouseButton>(mouse_button),
                                KeyState::Pressed });
        }
    }

    void EventDispatcher::poll_mouse_move() {
        Vec2i current_pos{ GetMouseX(), GetMouseY() };
        Vec2i delta = current_pos - m_mouse_position;

        if (delta == Vec2i::zero()) {
            return;
        }

        publish(MouseMoveEvent{ m_mouse_position, current_pos, delta });
        m_mouse_position = current_pos;
    }

    void EventDispatcher::poll_mouse_wheel() {
        auto mouse_wheel = GetMouseWheelMoveV();
        auto converted = Vec2i{ static_cast<int>(mouse_wheel.x),
                                static_cast<int>(mouse_wheel.y) };

        if (converted == Vec2i::zero()) {
            return;
        }

        publish(MouseWheelEvent{ converted });
    }

}  // namespace ui
