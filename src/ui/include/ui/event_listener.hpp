#pragma once

#include <print>
#include <variant>
#include "ui/event.hpp"

namespace ui {

    enum class EventListenerResult { Continue, Handled };

    EventListenerResult operator||(EventListenerResult a, EventListenerResult b);

    class GenericEventListener {
    public:
        virtual EventListenerResult handle(Event const& event) = 0;
    };

    template<std::convertible_to<Event> E>
    class SpecificEventListener {
    public:
        virtual EventListenerResult handle(E const& event) = 0;
    };

    template<std::convertible_to<Event>... Events>
    class EventListener : public GenericEventListener,
                          public virtual SpecificEventListener<Events>... {
    public:
        virtual ~EventListener() = default;

        EventListenerResult handle(Event const& event) final {
            return (handle_core<Events>(event) || ... || EventListenerResult::Continue);
        }

    private:
        template<std::convertible_to<Event> E>
        EventListenerResult handle_core(Event const& event) {
            if (auto specific_event = std::get_if<E>(&event)) {
                SpecificEventListener<E>* me = static_cast<SpecificEventListener<E>*>(this);
                return me->handle(*specific_event);
            }

            return EventListenerResult::Continue;
        }
    };

}  // namespace ui
