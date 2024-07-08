#include "ui/checkbox.hpp"
#include <ostream>

#include "ui/utils.hpp"

namespace ui {

    Checkbox::Checkbox(std::string&& id, std::string&& label, gfx::Font const& font)
        : Widget{std::move(id)}, m_label{std::move(label), font} {

        m_label.set_margin(Margin{
            static_cast<int>(m_box_size + m_box_spacing),
            0,
            0,
            0,
        });
    }

    Checkbox::Checkbox(std::string&& label, gfx::Font const& font)
        : Checkbox{get_next_id<Checkbox>("checkbox"), std::move(label), font} {}

    [[nodiscard]] RectI Checkbox::box_area() const {
        auto text_area = m_label.text_area();

        int x = text_area.origin.x - m_box_size - m_box_spacing;
        int y = (text_area.origin.y + text_area.size.y / 2.0f) - (m_box_size / 2.0f);

        return RectI{x, y, m_box_size, m_box_size};
    }

    void Checkbox::render(gfx::Renderer& renderer) const {
        renderer.draw_rect_outline(box_area(), m_box_thickness, m_box_color);

        if (m_is_checked) {
            RectF check_area = box_area().scale_from_center(0.5f);

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
        if (event.state != KeyState::Released) {
            return EventListenerResult::Continue;
        }

        if (not m_label.text_area().contains(event.position)
            and not box_area().contains(event.position))
        {
            return EventListenerResult::Continue;
        }

        m_is_checked = not m_is_checked;
        return EventListenerResult::Handled;
    }

}  // namespace ui
