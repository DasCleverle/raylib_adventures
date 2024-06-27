#include "ui/button.hpp"

#include <format>
#include <functional>

#include "gfx/font.hpp"
#include "ui/event.hpp"
#include "ui/event_dispatcher.hpp"

static inline std::string get_next_button_id() {
    static int counter = 0;
    return std::format("button_{}", counter++);
}

namespace ui {
    Button::Button(
        std::string&& id,
        std::string&& text,
        gfx::Font const& font,
        EventDispatcher& event_dispatcher
    )
        : Widget{std::move(id)}, m_label{text, font}, m_event_dispatcher{&event_dispatcher} {

        event_dispatcher.listen<MouseMoveEvent>(*this);
        event_dispatcher.listen<MouseEvent>(*this);
    }

    Button::Button(std::string&& text, gfx::Font const& font, EventDispatcher& event_dispatcher)
        : Button{get_next_button_id(), std::move(text), font, event_dispatcher} {}

    Button::~Button() {
        m_event_dispatcher->unlisten<MouseEvent>(*this);
        m_event_dispatcher->unlisten<MouseMoveEvent>(*this);
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
        m_is_hovered = area().contains(event.target);
        return EventListenerResult::Continue;
    }

    EventListenerResult Button::handle(MouseEvent const& event) {
        m_is_mouse_downed = event.state == KeyState::Pressed and event.button == MouseButton::Left
                            and area().contains(event.position);
        return EventListenerResult::Continue;
    }

}  // namespace ui
