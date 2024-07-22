#include "ui/checkbox.hpp"
#include "ui/utils.hpp"

namespace ui {

    Checkbox::Checkbox(
        std::string&& id,
        std::string&& label,
        gfx::Font const& font,
        EventDispatcher& dispatcher
    )
        : Widget{std::move(id)}, EventSource{dispatcher}, m_label{std::move(label), font} {

        m_label.set_margin(Margin{
            static_cast<int>(m_box_size + m_box_spacing),
            0,
            0,
            0,
        });
    }

    Checkbox::Checkbox(std::string&& label, gfx::Font const& font, EventDispatcher& dispatcher)
        : Checkbox{get_next_id<Checkbox>("checkbox"), std::move(label), font, dispatcher} {}

    [[nodiscard]] RectI Checkbox::box_area() const {
        auto text_area = m_label.text_area();

        int x = text_area.origin.x - m_box_size - m_box_spacing;
        int y = (text_area.origin.y + text_area.size.y / 2.0f) - (m_box_size / 2.0f);

        return RectI{x, y, m_box_size, m_box_size};
    }

    void Checkbox::render(gfx::Renderer& renderer) const {
        renderer.draw_rect_outline(box_area(), m_box_thickness, m_box_color);

        if (m_is_checked) {
            auto check_area = box_area().scale_from_center(0.5f);

            renderer.draw_rect_filled(check_area, m_box_color);
        }

        m_label.render(renderer);
    }

    void Checkbox::set_area(RectI const area) {
        Widget::set_area(area);
        m_label.set_area(area);
    }

    void Checkbox::set_margin(Margin const margin) {
        Widget::set_margin(margin);
        m_label.set_margin(Margin{
            static_cast<int>(m_box_size + m_box_spacing) + margin.left,
            margin.top,
            margin.right,
            margin.bottom,
        });
    }

    EventListenerResult Checkbox::handle(MouseEvent const& event) {
        auto contains = m_label.text_area().contains(event.position)
                        or box_area().contains(event.position);
        auto is_left = event.button == MouseButton::Left;
        auto is_pressed = event.state == KeyState::Pressed;

        std::println("handling checkbox click: mouse downed: {} ({})", m_is_mouse_downed, id());

        if (m_is_mouse_downed and contains and is_left and not is_pressed) {
            m_is_checked = not m_is_checked;
            m_is_mouse_downed = false;

            publish_event(CheckedEvent{this, m_is_checked, event});

            return EventListenerResult::Handled;
        }

        m_is_mouse_downed = contains and is_left and is_pressed;

        return EventListenerResult::Continue;
    }

}  // namespace ui
