#include "ui/event_dispatcher.hpp"

#include <raylib.h>
#include <array>
#include <print>
#include <vector>

#include "ui/event.hpp"
#include "ui/keycode.hpp"
#include "ui/keystate.hpp"
#include "utils/vec2.hpp"

static inline constexpr auto s_mouse_buttons = std::array{
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_SIDE,
    MOUSE_BUTTON_EXTRA,
    MOUSE_BUTTON_FORWARD,
    MOUSE_BUTTON_BACK,
};

namespace ui {

    void EventDispatcher::update() {
        poll_keyboard();
        poll_mouse();
        poll_mouse_move();
        poll_mouse_wheel();

        dispatch();
    }

    void EventDispatcher::dispatch() {
        while (not m_event_queue.empty()) {
            auto [event_only, event] = m_event_queue.front();
            m_event_queue.pop_front();

            for (auto [listener_only, listener] : m_listeners) {
                if (event_only != listener_only) {
                    continue;
                }

                listener->handle(event);
            }
        }
    }

    void EventDispatcher::poll_keyboard() {
        for (auto it = m_pressed_keys.begin(); it != m_pressed_keys.end();) {
            int key = *it;

            if (IsKeyReleased(key)) {
                publish(KeyboardEvent{static_cast<KeyCode>(key), KeyState::Released});
                it = m_pressed_keys.erase(it);
            }
            else {
                it++;
            }
        }

        int key;
        while ((key = GetKeyPressed()) != 0) {
            m_pressed_keys.push_back(key);
            publish(KeyboardEvent{static_cast<KeyCode>(key), KeyState::Pressed});
        }
    }

    void EventDispatcher::poll_mouse() {
        auto rl_pos = GetMousePosition();
        Vec2i position{static_cast<int>(rl_pos.x), static_cast<int>(rl_pos.y)};

        for (auto it = m_mouse_buttons.begin(); it != m_mouse_buttons.end();) {
            int mouse_button = *it;

            if (IsMouseButtonReleased(mouse_button)) {
                publish(MouseEvent{
                    static_cast<MouseButton>(mouse_button),
                    KeyState::Released,
                    position,
                });
                it = m_mouse_buttons.erase(it);
            }
            else {
                it++;
            }
        }

        for (auto mouse_button : s_mouse_buttons) {
            if (IsMouseButtonPressed(mouse_button)) {
                m_mouse_buttons.push_back(mouse_button);
                publish(MouseEvent{
                    static_cast<MouseButton>(mouse_button),
                    KeyState::Pressed,
                    position,
                });
            }
        }
    }

    void EventDispatcher::poll_mouse_move() {
        auto rl_pos = GetMousePosition();
        Vec2i current_pos{static_cast<int>(rl_pos.x), static_cast<int>(rl_pos.y)};
        Vec2i delta = current_pos - m_mouse_position;

        if (delta == Vec2i::zero()) {
            return;
        }

        publish(MouseMoveEvent{m_mouse_position, current_pos, delta});
        m_mouse_position = current_pos;
    }

    void EventDispatcher::poll_mouse_wheel() {
        auto rl_delta = GetMouseWheelMoveV();
        auto rl_pos = GetMousePosition();

        auto position = Vec2i{static_cast<int>(rl_pos.x), static_cast<int>(rl_pos.y)};
        auto delta = Vec2i{static_cast<int>(rl_delta.x), static_cast<int>(rl_delta.y)};

        if (delta == Vec2i::zero()) {
            return;
        }

        publish(MouseWheelEvent{position, delta});
    }

}  // namespace ui
