#pragma once

#include "gfx/font.hpp"
#include "widget.hpp"

namespace ui {

    enum class HorizontalAlign { Left = 0, Center = 1, Right = 2 };

    enum class VerticalAlign { Top = 0, Middle = 1, Bottom = 2 };

    class Label final : public Widget {
    private:
        struct Line {
            std::string text;
            Vec2f size;
        };

        std::string m_text;
        std::vector<Line> m_lines;

        float m_line_height{1};
        gfx::Font const* m_font;
        gfx::Color m_color{gfx::Colors::Black};
        HorizontalAlign m_align{HorizontalAlign::Center};
        VerticalAlign m_vertical_align{VerticalAlign::Middle};

        void recalc_lines();
        void render_line(gfx::Renderer& renderer, Line const& line, int line_index, int line_count)
            const;

    public:
        Label(std::string text, gfx::Font const& font);

        Label(Label const&) = delete;
        Label& operator=(Label const&) = delete;
        Label(Label&&) = default;
        Label& operator=(Label&&) = default;
        ~Label() = default;

        void render(gfx::Renderer& renderer) const override;

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
