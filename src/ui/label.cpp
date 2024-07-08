#include "ui/label.hpp"

#include <cassert>
#include <functional>

#include "utils/strings.hpp"

static inline std::string get_next_label_id() {
    static int counter = 0;
    return std::format("button_{}", counter++);
}

namespace ui {
    Label::Label(std::string&& text, gfx::Font const& font)
        : Widget{get_next_label_id()}, m_text{std::move(text)}, m_font{&font} {
        recalc_lines();
    }

    void Label::render(gfx::Renderer& renderer) const {
        for (auto const& line : m_lines) {
            render_line(renderer, line);
        }
    }

    void Label::render_line(gfx::Renderer& renderer, Line const& line) const {
        renderer.draw_text(*m_font, line.text.c_str(), line.area.origin, m_color);
    }

    std::vector<Label::Line> Label::get_lines() const {
        std::vector<Line> lines;
        auto const area = draw_area();

        if (auto const text_size = m_font->measure_text(m_text.c_str()); text_size.x < area.size.x)
        {
            RectI text_area{
                {0, 0},
                text_size
            };
            lines.emplace_back(m_text, text_area);
            return lines;
        }

        std::vector<std::string> words = split(m_text, ' ');

        auto begin = words.begin();
        auto end = std::prev(words.end());

        do {
            auto current_attempt = join(begin, end, ' ');

            if (auto const text_size = m_font->measure_text(current_attempt.c_str());
                text_size.x < area.size.x)
            {
                RectI text_area{
                    {0, 0},
                    text_size
                };
                lines.emplace_back(current_attempt, text_area);

                begin = end;
                end = words.end();
            }
            else {
                end--;
            }
        } while (begin != words.end() and end != begin);

        return lines;
    }

    void Label::recalc_lines() {
        m_lines = get_lines();

        auto const line_count = m_lines.size();

        if (line_count == 0) {
            return;
        }

        auto const area = draw_area();

        for (int line_index = 0; line_index < line_count; line_index++) {
            auto& line = m_lines[line_index];

            auto const x = std::invoke([&]() {
                switch (m_align) {
                    case ui::HorizontalAlign::Left:
                        return static_cast<float>(area.origin.x);

                    case ui::HorizontalAlign::Center:
                        return area.center().x - line.area.size.x / 2.0f;

                    case ui::HorizontalAlign::Right:
                        return static_cast<float>(area.origin.x + area.size.x - line.area.size.x);
                }

                assert(false and "unreachable");
            });

            auto const y = std::invoke([&] {
                auto line_height = line.area.size.y * m_line_height;

                switch (m_vertical_align) {
                    case ui::VerticalAlign::Top:
                        return area.origin.y + (line_index * line_height);

                    case ui::VerticalAlign::Middle:
                        return area.center().y - (line_count / 2.0f * line_height)
                               + (line_index * line_height);

                    case ui::VerticalAlign::Bottom:
                        return area.origin.y + area.size.y
                               - ((line_count - line_index) * line_height);
                }

                assert(false and "unreachable");
            });

            line.area.origin = Vec2i{
                static_cast<int>(std::ceil(x)),
                static_cast<int>(std::ceil(y)),
            };
        }
    }

    [[nodiscard]] RectI Label::text_area() const {
        RectI text_area{};

        for (auto const line : m_lines) {
            text_area.origin.x = text_area.origin.x == 0
                                     ? line.area.origin.x
                                     : std::min(text_area.origin.x, line.area.origin.x);
            text_area.origin.y = text_area.origin.y == 0
                                     ? line.area.origin.y
                                     : std::min(text_area.origin.y, line.area.origin.y);

            text_area.size.x = std::max(text_area.size.x, line.area.size.x);
            text_area.size.y += line.area.size.y * m_line_height;
        }

        return text_area;
    }

}  // namespace ui
