
#include "ui/event_listener.hpp"

namespace ui {
    EventListenerResult operator||(EventListenerResult a, EventListenerResult b) {
        return (a == EventListenerResult::Handled || b == EventListenerResult::Handled)
                   ? EventListenerResult::Handled
                   : EventListenerResult::Continue;
    }
}  // namespace ui
