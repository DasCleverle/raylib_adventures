#include "ui/button.hpp"

#include <format>
#include <functional>

#include "gfx/font.hpp"
#include "ui/event.hpp"
#include "ui/event_listener.hpp"
#include "ui/keystate.hpp"

static inline std::string get_next_button_id() {
    static int counter = 0;
    return std::format("button_{}", counter++);
}

namespace ui {
    Button::Button(std::string&& id, std::string&& text, gfx::Font const& font, EventDispatcher& dispatcher)
        : Widget{std::move(id)}, EventSource{dispatcher}, m_label{text, font} {}

    Button::Button(std::string&& text, gfx::Font const& font, EventDispatcher& dispatcher)
        : Button{get_next_button_id(), std::move(text), font, dispatcher} {}

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

        renderer.draw_rect_filled(draw_area(), color);
        m_label.render(renderer);
    }

    EventListenerResult Button::handle(MouseMoveEvent const& event) {
        m_is_hovered = area().contains(event.target);
        return EventListenerResult::Continue;
    }

    EventListenerResult Button::handle(MouseEvent const& event) {
        auto contains = area().contains(event.position);
        auto is_left = event.button == MouseButton::Left;
        auto is_pressed = event.state == KeyState::Pressed;

        if (m_is_mouse_downed and contains and is_left and not is_pressed) {
            publish_event(ClickEvent{this, event});
        }

        m_is_mouse_downed = contains and is_left && is_pressed;
        return EventListenerResult::Continue;
    }

}  // namespace ui
