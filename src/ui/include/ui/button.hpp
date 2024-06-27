#pragma once

#include "event.hpp"
#include "event_dispatcher.hpp"
#include "event_listener.hpp"
#include "label.hpp"
#include "widget.hpp"

namespace ui {

    class Button final : public Widget,
                         public EventListener<MouseMoveEvent>,
                         public EventListener<MouseEvent> {
    private:
        Label m_label;
        gfx::Color m_color{gfx::Colors::DarkGray};
        gfx::Color m_hover_color{gfx::Colors::Gray};
        gfx::Color m_click_color{gfx::Colors::Blue};

        EventDispatcher& m_event_dispatcher;
        bool m_is_hovered{false};
        bool m_is_mouse_downed{false};

    public:
        Button(
            std::string text,
            gfx::Font const& font,
            gfx::Color const color,
            EventDispatcher& event_dispatcher
        );
        ~Button();

        void set_color(gfx::Color const color) {
            m_color = color;
        }

        void render(gfx::Renderer& renderer) const override;

        void set_area(RectI const area) override {
            Widget::set_area(area);
            m_label.set_area(area);
        }

        EventListenerResult handle(MouseMoveEvent const& event) override;

        EventListenerResult handle(MouseEvent const& event) override;
    };

}  // namespace ui
