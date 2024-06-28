#pragma once

#include <algorithm>
#include <cassert>
#include <print>
#include <vector>

#include "event_listener.hpp"
#include "utils/vec2.hpp"

namespace ui {

    class EventDispatcher final {
    private:
        std::vector<GenericEventListener*> m_listeners;
        std::vector<Event> m_event_queue;

        std::vector<int> m_pressed_keys{};
        std::vector<int> m_mouse_buttons{};
        Vec2i m_mouse_position;

        void poll_keyboard();
        void poll_mouse();
        void poll_mouse_move();
        void poll_mouse_wheel();

        void dispatch();

    public:
        EventDispatcher() = default;
        EventDispatcher(EventDispatcher const&) = delete;
        EventDispatcher(EventDispatcher&&) = default;
        EventDispatcher& operator=(EventDispatcher const&) = delete;
        EventDispatcher& operator=(EventDispatcher&&) = default;

        void update();

        template<std::derived_from<GenericEventListener> L>
        void listen(L& listener) {
            m_listeners.push_back(static_cast<GenericEventListener*>(&listener));
        }

        template<std::derived_from<GenericEventListener> L>
        void unlisten(L& listener) {
            auto it = std::find(
                m_listeners.begin(),
                m_listeners.end(),
                static_cast<GenericEventListener*>(&listener)
            );
            m_listeners.erase(it);
        }

        template<std::convertible_to<Event> T>
        void publish(T const& event) {
            m_event_queue.push_back(event);
        }
    };
}  // namespace ui
