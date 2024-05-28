#include "ui/button.hpp"

#include <functional>

#include "gfx/font.hpp"
#include "ui/event.hpp"
#include "ui/event_dispatcher.hpp"

namespace ui {
    Button::Button(
        std::string text,
        gfx::Font const& font,
        gfx::Color const color,
        EventDispatcher& event_dispatcher
    )
        : m_label{text, font}, m_color{color}, m_event_dispatcher{event_dispatcher} {

        event_dispatcher.listen<MouseMoveEvent>(*this);
        event_dispatcher.listen<MouseEvent>(*this);
    }

    Button::~Button() {
        m_event_dispatcher.unlisten<MouseEvent>(*this);
        m_event_dispatcher.unlisten<MouseMoveEvent>(*this);
    }

    void Button::render(gfx::Renderer& renderer) const {
        auto const color = std::invoke([&] {
            if (m_is_mouse_downed) {
                return m_click_color;
            }

            if (m_is_hovered) {
                return m_hover_color;
            }

            return m_color;
        });

        renderer.draw_rect_filled(area(), color);
        m_label.render(renderer);
    }

    EventListenerResult Button::handle(MouseMoveEvent const& event) {
        m_is_hovered = area().contains(Vec2f{event.target});
        return EventListenerResult::Continue;
    }

    EventListenerResult Button::handle(MouseEvent const& event) {
        m_is_mouse_downed = event.state == KeyState::Pressed and event.button == MouseButton::Left
                            and area().contains(Vec2f{event.position});
        return EventListenerResult::Continue;
    }

}  // namespace ui
