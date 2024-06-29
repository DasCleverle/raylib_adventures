#pragma once

#include "event.hpp"
#include "event_listener.hpp"
#include "event_source.hpp"
#include "label.hpp"
#include "widget.hpp"

namespace ui {

    class Button final : public Widget,
                         public EventListener<MouseMoveEvent, MouseEvent>,
                         public EventSource {
    private:
        Label m_label;
        gfx::Color m_color{gfx::Colors::DarkGray};
        gfx::Color m_hover_color{gfx::Colors::Gray};
        gfx::Color m_click_color{gfx::Colors::Blue};

        bool m_is_hovered{false};
        bool m_is_mouse_downed{false};

    public:
        Button(std::string&& id, std::string&& text, gfx::Font const& font, EventDispatcher& dispatcher);
        Button(std::string&& text, gfx::Font const& font, EventDispatcher& dispatcher);

        Button(Button const&) = delete;
        Button& operator=(Button const&) = delete;
        Button(Button&&) = default;
        Button& operator=(Button&&) = default;

        void set_color(gfx::Color const color) {
            m_color = color;
        }

        void set_hover_color(gfx::Color const color) {
            m_hover_color = color;
        }

        void set_click_color(gfx::Color const color) {
            m_click_color = color;
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
