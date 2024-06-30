#include "ui/label.hpp"

#include <cassert>
#include <functional>

#include "utils/strings.hpp"

static inline std::string get_next_label_id() {
    static int counter = 0;
    return std::format("button_{}", counter++);
}

namespace ui {
    Label::Label(std::string text, gfx::Font const& font)
        : Widget{get_next_label_id()}, m_text{std::move(text)}, m_font{&font} {
        recalc_lines();
    }

    void Label::render(gfx::Renderer& renderer) const {
        auto size = m_lines.size();

        for (int i = 0; i < size; i++) {
            render_line(renderer, m_lines[i], i, size);
        }
    }

    void Label::render_line(gfx::Renderer& renderer, Line const& line, int line_index, int line_count)
        const {

        auto const area = draw_area();

        auto const x = std::invoke([&]() {
            switch (m_align) {
                case ui::HorizontalAlign::Left:
                    return static_cast<float>(area.origin.x);

                case ui::HorizontalAlign::Center:
                    return (area.center() - line.size / 2).x;

                case ui::HorizontalAlign::Right:
                    return area.origin.x + area.size.x - line.size.x;
            }

            assert(false and "unreachable");
        });

        auto const y = std::invoke([&] {
            auto line_height = line.size.y * m_line_height;

            switch (m_vertical_align) {
                case ui::VerticalAlign::Top:
                    return static_cast<float>(area.origin.y + (line_index * line_height));

                case ui::VerticalAlign::Middle:
                    return area.center().y - (line_count / 2.0f * line_height)
                           + (line_index * line_height);

                case ui::VerticalAlign::Bottom:
                    return area.origin.y + area.size.y - ((line_count - line_index) * line_height);
            }

            assert(false and "unreachable");
        });

        auto const text_position = Vec2f{x, y};
        renderer.draw_text(*m_font, line.text.c_str(), text_position, m_color);
        // renderer.draw_rect_outline(RectF{text_position, line.size}, 1.0f, gfx::Colors::Red);
    }

    void Label::recalc_lines() {
        m_lines.clear();

        auto const area = draw_area();

        if (auto const text_size = m_font->measure_text(m_text.c_str()); text_size.x < area.size.x)
        {
            m_lines.emplace_back(m_text, text_size);
            return;
        }

        std::vector<std::string> words = split(m_text, ' ');

        auto begin = words.begin();
        auto end = std::prev(words.end());

        do {
            auto current_attempt = join(begin, end, ' ');

            if (auto const text_size = m_font->measure_text(current_attempt.c_str());
                text_size.x < area.size.x)
            {
                m_lines.emplace_back(current_attempt, text_size);

                begin = end;
                end = words.end();
            }
            else {
                end = std::prev(end);
            }
        } while (begin != words.end() and end != begin);

        if (m_lines.size() == 0) {
            m_lines.emplace_back("Error:", m_font->measure_text("Error:"));
            m_lines.emplace_back("Text", m_font->measure_text("Text"));
            m_lines.emplace_back("too", m_font->measure_text("too"));
            m_lines.emplace_back("big", m_font->measure_text("big"));
        }
    }

}  // namespace ui
