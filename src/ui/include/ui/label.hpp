#pragma once

#include <cmath>
#include "align.hpp"
#include "gfx/font.hpp"
#include "widget.hpp"

namespace ui {

    class Label final : public Widget {
    private:
        struct Line {
            std::string text;
            RectF area;
        };

        std::string m_text;
        std::vector<Line> m_lines;

        float m_line_height{1};
        gfx::Font const* m_font;
        gfx::Color m_color{gfx::Colors::Black};
        HorizontalAlign m_align{HorizontalAlign::Center};
        VerticalAlign m_vertical_align{VerticalAlign::Middle};

        std::vector<Line> get_lines() const;
        void recalc_lines();
        void render_line(gfx::Renderer& renderer, Line const& line) const;

    public:
        Label(std::string&& text, gfx::Font const& font);

        Label(Label const&) = delete;
        Label& operator=(Label const&) = delete;
        Label(Label&&) = default;
        Label& operator=(Label&&) = default;
        ~Label() = default;

        void render(gfx::Renderer& renderer) const override;

        [[nodiscard]] RectI text_area() const;

        void set_area(RectI const area) override {
            Widget::set_area(area);
            recalc_lines();
        }

        void set_text(std::string&& text) {
            m_text = std::move(text);
            recalc_lines();
        }
    };
}  // namespace ui
