#include "ui/button.hpp"

#include <functional>
#include <print>

#include "gfx/font.hpp"
#include "ui/event.hpp"
#include "ui/event_listener.hpp"
#include "ui/keystate.hpp"
#include "ui/utils.hpp"

namespace ui {
    Button::Button(std::string&& id, std::string&& text, gfx::Font const& font, EventDispatcher& dispatcher)
        : Widget{std::move(id)}, EventSource{dispatcher}, m_label{std::move(text), font} {}

    Button::Button(std::string&& text, gfx::Font const& font, EventDispatcher& dispatcher)
        : Button{get_next_id<Button>("button"), std::move(text), font, dispatcher} {}

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
            m_is_mouse_downed = false;

            publish_event(ClickEvent{this, event});

            return EventListenerResult::Handled;
        }

        m_is_mouse_downed = contains and is_left and is_pressed;

        return EventListenerResult::Continue;
    }

}  // namespace ui
