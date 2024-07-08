#pragma once

#include "gfx/color.hpp"
#include "ui/label.hpp"
#include "ui/widget.hpp"

namespace ui {

    class Checkbox : public Widget {
    private:
        float m_box_size{30};
        float m_box_spacing{10};
        float m_box_thickness{3};
        gfx::Color m_box_color{gfx::Colors::Black};

        Label m_label;

    public:
        Checkbox(std::string&& id, std::string&& label, gfx::Font const& font);
        Checkbox(std::string&& label, gfx::Font const& font);

        Checkbox(Checkbox const&) = delete;
        Checkbox& operator=(Checkbox const&) = delete;
        Checkbox(Checkbox&&) = default;
        Checkbox& operator=(Checkbox&&) = default;
        ~Checkbox() = default;

        void set_area(RectI const area) override;

        void set_margin(Margin const margin) override;

        void render(gfx::Renderer& renderer) const override;
    };
}  // namespace ui
