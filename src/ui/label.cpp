#include "ui/label.hpp"
#include <cassert>
#include <functional>

namespace ui {
    Label::Label(std::string text, gfx::Font const& font)
        : m_text{std::move(text)}, m_font{&font} {}

    void Label::render(gfx::Renderer& renderer) const {
        auto const text_size = m_font->measure_text(m_text.c_str());

        auto const x = std::invoke([&]() {
            switch (m_align) {
                case ui::HorizontalAlign::Left:
                    return area().origin.x;

                case ui::HorizontalAlign::Center:
                    return (area().center() - text_size / 2).x;

                case ui::HorizontalAlign::Right:
                    return area().origin.x + area().size.x - text_size.x;
            }

            assert(false and "unreachable");
        });

        auto const y = std::invoke([&] {
            switch (m_vertical_align) {
                case ui::VerticalAlign::Top:
                    return area().origin.y;

                case ui::VerticalAlign::Middle:
                    return (area().center() - text_size / 2).y;

                case ui::VerticalAlign::Bottom:
                    return area().origin.y + area().size.y - text_size.y;
            }

            assert(false and "unreachable");
        });

        auto const text_position = Vec2f{x, y};

        renderer.draw_text(*m_font, m_text.c_str(), text_position, m_color);
    }
}  // namespace ui
