#include "ui/checkbox.hpp"

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

    void Checkbox::render(gfx::Renderer& renderer) const {
        auto text_area = m_label.text_area();

        float x = text_area.origin.x - m_box_size - m_box_spacing;
        float y = (text_area.origin.y + text_area.size.y / 2.0f) - (m_box_size / 2.0f);

        renderer.draw_rect_outline(RectF{x, y, m_box_size, m_box_size}, m_box_thickness, m_box_color);
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

}  // namespace ui
