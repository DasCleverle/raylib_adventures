#pragma once

#include <memory>
#include <vector>

#include "event.hpp"
#include "event_listener.hpp"

namespace ui {

    class EventDispatcher {
    private:
        std::vector<std::pair<EventType, std::weak_ptr<EventListenerBase>>>
            m_listeners;
        std::vector<int> m_pressed_keys{};

        struct Deleter {
            EventDispatcher& m_dispatcher;

            void operator()(EventListenerBase* ptr) {}
        };

    public:
        void poll();

        template<IsEvent T, std::derived_from<EventListener<T>> L>
        void listen(std::shared_ptr<L> const& listener) {
            m_listeners.emplace_back(
                static_cast<EventType>(T::type),
                std::static_pointer_cast<EventListenerBase>(listener)
            );
        }

        template<IsEvent T>
        void unlisten(EventListener<T> const& listener) {
            for (auto it = m_listeners.begin(); it != m_listeners.end();) {
                auto const& [_, l] = *it;

                if (listener == l) {
                    it = m_listeners.erase(it);
                }
            }
        }

        template<IsEvent T>
        void publish(T const& event) {
            for (auto it = m_listeners.begin(); it != m_listeners.end();) {
                auto const& [type, listener] = *it;

                if (listener.expired()) {
                    it = m_listeners.erase(it);
                }
                else if (type == T::type) {
                    listener.lock()->handle(event);
                    it++;
                }
                else {
                    it++;
                }
            }
        }
    };
}  // namespace ui
