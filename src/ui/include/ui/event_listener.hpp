#pragma once

#include <type_traits>

#include "event.hpp"

namespace ui {

    class EventDispatcher;

    enum class EventListenerResult { Continue, Handled };

    class EventListenerBase {
        friend class EventDispatcher;

    private:
        virtual EventListenerResult handle(Event const& event) = 0;
    };

    template<IsEvent T>
    class EventListener : public EventListenerBase {
    private:
        EventListenerResult handle(Event const& event) override {
            return std::visit(
                [this](auto const& unpacked_event) {
                    using U = std::decay_t<decltype(unpacked_event)>;

                    if constexpr (std::is_same_v<U, T>) {
                        return handle(unpacked_event);
                    }

                    return EventListenerResult::Continue;
                },
                event
            );
        }

    public:
        virtual EventListenerResult handle(T const& event) = 0;
    };

}  // namespace ui
