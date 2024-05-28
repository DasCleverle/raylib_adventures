#pragma once

#include <any>
#include <typeindex>
#include <vector>

#include "event_listener.hpp"
#include "utils/vec2.hpp"

namespace ui {

    class EventDispatcher final {
    private:
        std::vector<std::pair<std::type_index, std::any>> m_listeners;

        std::vector<int> m_pressed_keys{};
        std::vector<int> m_mouse_buttons{};
        Vec2i m_mouse_position;

        void poll_keyboard();
        void poll_mouse();
        void poll_mouse_move();
        void poll_mouse_wheel();

    public:
        EventDispatcher() = default;
        EventDispatcher(EventDispatcher const&) = delete;
        EventDispatcher(EventDispatcher&&) = default;
        EventDispatcher& operator=(EventDispatcher const&) = delete;
        EventDispatcher& operator=(EventDispatcher&&) = default;

        void poll() {
            poll_keyboard();
            poll_mouse();
            poll_mouse_move();
            poll_mouse_wheel();
        }

        template<typename T, std::derived_from<EventListener<T>> L>
        void listen(L& listener) {
            m_listeners.emplace_back(typeid(T), static_cast<EventListener<T>*>(&listener));
        }

        template<typename T, std::derived_from<EventListener<T>> L>
        void unlisten(L& listener) {
            for (auto it = m_listeners.begin(); it != m_listeners.end();) {
                auto const& [type, l] = *it;

                if (type != typeid(T)) {
                    it++;
                    continue;
                }

                auto const ptr = std::any_cast<EventListener<T>*>(l);

                if (ptr == nullptr or ptr == &listener) {
                    it = m_listeners.erase(it);
                }
                else {
                    it++;
                }
            }
        }

        template<typename T>
        void publish(T const& event) {
            for (auto it = m_listeners.begin(); it != m_listeners.end();) {
                auto const& [type, listener] = *it;

                if (type != typeid(T)) {
                    it++;
                    continue;
                }

                auto ptr = std::any_cast<EventListener<T>*>(listener);

                if (ptr == nullptr) {
                    it = m_listeners.erase(it);
                    continue;
                }

                auto const result = ptr->handle(event);

                if (result == EventListenerResult::Handled) {
                    break;
                }

                it++;
            }
        }
    };
}  // namespace ui
