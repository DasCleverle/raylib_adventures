#pragma once

#include <algorithm>
#include <cassert>
#include <deque>
#include <memory>
#include <print>
#include <utility>
#include <vector>

#include "event_listener.hpp"
#include "utils/vec2.hpp"

namespace ui {

    class EventSource;

    class EventDispatcher final {
    private:
        std::vector<std::pair<EventSource const*, std::shared_ptr<GenericEventListener>>> m_listeners;
        std::deque<std::pair<EventSource const*, Event>> m_event_queue;

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

        void listen(std::shared_ptr<GenericEventListener> listener) {
            m_listeners.emplace_back(nullptr, listener);
        }

        void listen(EventSource const& only, std::shared_ptr<GenericEventListener> listener) {
            m_listeners.emplace_back(&only, listener);
        }

        void unlisten(GenericEventListener const& listener) {
            auto it = std::find_if(m_listeners.begin(), m_listeners.end(), [&listener](auto pair) {
                return pair.second.get() == &listener;
            });
            m_listeners.erase(it);
        }

        void publish(Event const& event) {
            m_event_queue.emplace_back(nullptr, event);
        }

        template<std::convertible_to<Event> T>
        void publish(EventSource const& only, T const& event) {
            m_event_queue.emplace_back(&only, event);
        }
    };
}  // namespace ui
