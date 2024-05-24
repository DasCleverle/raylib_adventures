#pragma once

#include <any>
#include <memory>
#include <typeindex>
#include <vector>

#include "event_listener.hpp"
#include "utils/vec2.hpp"

namespace ui {

    class EventDispatcher {
    private:
        std::vector<std::pair<std::type_index, std::any>> m_listeners;

        std::vector<int> m_pressed_keys{};
        std::vector<int> m_mouse_buttons{};
        Vec2i m_mouse_position;

        void poll_keyboard();
        void poll_mouse();
        void poll_mouse_move();
        void poll_mouse_wheel();

        void check_mouse_button(int mouse_button);

    public:
        void poll() {
            poll_keyboard();
            poll_mouse();
            poll_mouse_move();
            poll_mouse_wheel();
        }

        template<typename T, std::derived_from<EventListener<T>> L>
        void listen(std::shared_ptr<L> const& listener) {
            m_listeners.emplace_back(
                typeid(T),
                std::weak_ptr<EventListener<T>>{ listener }
            );
        }

        template<typename T>
        void unlisten(EventListener<T> const& listener) {
            for (auto it = m_listeners.begin(); it != m_listeners.end();) {
                auto const& [type, l] = *it;

                if (type != typeid(T)) {
                    it++;
                    continue;
                }

                std::weak_ptr<EventListener<T>> ptr =
                    std::any_cast<std::weak_ptr<EventListener<T>>>(l);

                if (ptr.expired() || ptr.lock() == listener) {
                    it = m_listeners.erase(it);
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

                std::weak_ptr<EventListener<T>> ptr =
                    std::any_cast<std::weak_ptr<EventListener<T>>>(listener);

                if (ptr.expired()) {
                    it = m_listeners.erase(it);
                    continue;
                }

                auto const result = ptr.lock()->handle(event);

                if (result == EventListenerResult::Handled) {
                    break;
                }

                it++;
            }
        }
    };
}  // namespace ui
