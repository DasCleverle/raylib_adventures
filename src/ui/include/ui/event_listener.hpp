#pragma once

namespace ui {

    enum class EventListenerResult { Continue, Handled };

    template<typename T>
    class EventListener {
    public:
        virtual ~EventListener() = default;
        virtual EventListenerResult handle(T const& event) = 0;
    };

}  // namespace ui
