#include "ui/button.hpp"

#include <format>
#include <functional>

#include "gfx/font.hpp"
#include "ui/event.hpp"

static inline std::string get_next_button_id() {
    static int counter = 0;
    return std::format("button_{}", counter++);
}

namespace ui {
    Button::Button(std::string&& id, std::string&& text, gfx::Font const& font)
        : Widget{std::move(id)}, m_label{text, font} {}

    Button::Button(std::string&& text, gfx::Font const& font)
        : Button{get_next_button_id(), std::move(text), font} {}

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
