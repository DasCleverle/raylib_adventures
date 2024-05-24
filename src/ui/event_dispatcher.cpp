#include "ui/event_dispatcher.hpp"

#include <raylib.h>
#include <vector>

#include "ui/event.hpp"
#include "ui/keycode.hpp"
#include "ui/keystate.hpp"

template<typename T>
static bool contains(std::vector<T> const& v, T item) {
    return std::find(v.begin(), v.end(), item) != v.end();
}

namespace ui {

    void EventDispatcher::poll() {
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

}  // namespace ui
