#pragma once

#include <memory>
#include <print>

#include "ui/event_dispatcher.hpp"
#include "ui/event_listener.hpp"

namespace ui {

    class EventSource {
    private:
        std::vector<std::shared_ptr<GenericEventListener>> m_listeners;
        EventDispatcher* m_dispatcher;

    public:
        EventSource(EventSource const&) = delete;
        EventSource& operator=(EventSource const&) = delete;

        EventSource(EventSource&& other) {
            m_listeners = other.m_listeners;
            m_dispatcher = other.m_dispatcher;

            for (auto listener : m_listeners) {
                m_dispatcher->unlisten(*listener);
                m_dispatcher->listen(*this, listener);
            }

            other.m_listeners.clear();
            other.m_dispatcher = nullptr;
        }

        EventSource& operator=(EventSource&& other) {
            for (auto listener : m_listeners) {
                m_dispatcher->unlisten(*listener);
                other.m_dispatcher->listen(*this, listener);
            }

            for (auto listener : other.m_listeners) {
                other.m_dispatcher->unlisten(*listener);
                other.m_dispatcher->listen(*this, listener);

                m_listeners.push_back(listener);
            }

            m_dispatcher = other.m_dispatcher;

            other.m_listeners.clear();
            other.m_dispatcher = nullptr;

            return *this;
        }

        virtual ~EventSource() {
            for (auto listener : m_listeners) {
                m_dispatcher->unlisten(*listener);
            }
        }

        void listen(std::shared_ptr<GenericEventListener> listener) {
            m_listeners.push_back(listener);
            m_dispatcher->listen(*this, listener);
        }

    protected:
        EventSource(EventDispatcher& dispatcher)
            : m_dispatcher{&dispatcher} {}

        void publish_event(Event const& event) {
            m_dispatcher->publish(*this, event);
        }
    };

}  // namespace ui
