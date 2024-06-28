#pragma once

#include "gfx/font.hpp"
#include "widget.hpp"

namespace ui {

    enum class HorizontalAlign { Left = 0, Center = 1, Right = 2 };

    enum class VerticalAlign { Top = 0, Middle = 1, Bottom = 2 };

    class Label final : public Widget {
    private:
        std::string m_text;
        gfx::Font const* m_font;
        gfx::Color m_color{gfx::Colors::Black};
        HorizontalAlign m_align{HorizontalAlign::Center};
        VerticalAlign m_vertical_align{VerticalAlign::Middle};

    public:
        Label(std::string text, gfx::Font const& font);

        Label(Label const&) = delete;
        Label& operator=(Label const&) = delete;
        Label(Label&&) = default;
        Label& operator=(Label&&) = default;
        ~Label() = default;

        void render(gfx::Renderer& renderer) const override;
    };
}  // namespace ui
